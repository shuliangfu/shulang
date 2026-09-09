/* seeds/labi_path_pure.from_x.c — G-02f-267/429/L P2 link_abi L0 path pure → R2 full
 * Logic source: src/runtime/labi_path_pure.x
 * Hybrid: XLANG_LABI_PATH_PURE_FROM_X + ld -r into runtime_link_abi.o
 *
 * R2 full（2026-07-14 / wave114–116 / wave146–149）：公共业务符号由 full .x 提供：
 *   labi_suffix_eq2/eq4 + link_abi_ld_argv_entry_is_obj + xlang_output_is_elf_o
 *   + xlang_output_want_exe + xlang_path_has_sep + xlang_path_last_sep
 *   + xlang_asm_ld_lib_root_ptr_usable (wave114 low-tag)
 *   + xlang_asm_ld_lib_root_default (wave115 XLANG_LIB/"." ; Cap residual link_abi_getenv wave223)
 *   + xlang_asm_ld_try_under_lib_roots (wave116 pure join; Cap residual skip+bank)
 *   + link_abi_asm_ld_argv_has_obj (wave146 pure scan; Cap residual realpath)
 *   + link_abi_asm_ld_argv_push_stable (wave147 pure bank+dedup+append; Cap residual bank_push)
 *   + link_abi_asm_ld_push_obj (wave148 pure resolve orch; Cap residual skip/rel/bank/diag)
 *   + link_abi_asm_ld_push_glue_after_std (wave149 pure have_std+ensure orch; Cap residual call_ensure)
 *   + link_abi_asm_ld_push_minimal_runtime_objs (wave150 pure triple push_obj; Cap residual *_o_path)
 *   + xlang_asm_ld_append_user_extra_o_files (wave151 pure CLI extra .o append; Cap residual table+access)
 *   + xlang_runtime_compiler_o_path_copy (wave160 pure join compiler-dir/leaf; Cap residual resolve)
 *   + xlang_repo_root_from_argv0 (wave162 pure strip parent / process.o walk; Cap residual resolve+rel)
 *   + xlang_runtime_panic_o_path (wave163 pure cwd/argv0 ladder; Cap residual realpath+getcwd+skip)
 *   + xlang_crt0_user_o_path (wave164 pure cwd/argv0 ladder; Cap residual realpath_cap+getcwd)
 *   + xlang_freestanding_io_o_path (wave165 pure cwd/argv0 ladder; Cap residual realpath_cap+getcwd)
 *   + xlang_std_async_scheduler_o_path (wave166 pure cwd/argv0 ladder; Cap residual realpath_cap+getcwd;
 *     step3 realpath(argv0)+parent+/../std/async)
 *   + scheduler_o_for_task_link (wave180 pure task.o→scheduler.o rewrite; Cap residual
 *     path_readable + realpath_cap; static 4096/4096 BSS)
 *   + xlang_bootstrap_nostdlib_stubs_o_path (wave181 pure cwd realpath + compiler-dir/leaf;
 *     Cap residual realpath_cap + xlang_resolve_compiler_dir; static 4096/4096 BSS)
 *   + 29× thin xlang_runtime_*_o_path (wave183 pure BSS + compiler_o_path_copy;
 *     asm_io_stubs … ed25519_ref10_glue; static 4096 BSS each)
 *   + xlang_empty_cstr / xlang_std_io_o_path / xlang_std_compress_o_path /
 *     xlang_asm_ld_effective_link_argv0 (wave184 pure empty durable "" + effective link orch;
 *     Cap residual resolve for synthetic compiler-dir/xlang)
 *   + xlang_rel_o_path_from_argv0 (wave185 pure realpath/cwd/argv0 ladder; Cap residual
 *     realpath_cap + getcwd + link_abi_cstr_dup + skip_missing; heap return)
 *   + xlang_invoke_cc_set/clear_user_o_files (wave189 pure argv .o scan; Cap residual reset/push)
 *   + count
 * Cap residual（mega rest 冷路径）：Windows #if '\\' 分隔符；产品 PREFER 走 .x POSIX。
 * FROM_X 下本文件仅前向声明 + slice marker（产品 rest 业务 H=0）。
 * 冷启动/无 PREFER 时仍编译完整 C 体（可与 mega 并存）。
 *
 */
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

/* Cap residual used by wave116 cold twin (product hybrid: path_io + gates). */
const char *asm_link_obj_skip_missing(const char *path);
/* wave223 G.7: env lookup authority = public pure thin link_abi_getenv (labi_diag_pure). */
const char *link_abi_getenv(const char *name);
const char *xlang_asm_ld_bank_push(void *b, const char *path);
/* Cap residual used by wave146 argv_has_obj / wave185 rel_o cold twin (mega always provides). */
const char *link_abi_realpath_cap(const char *path, char *out);
/* Cap residual wave185: heap cstr dup (mega always; wraps strdup). */
const char *link_abi_cstr_dup(const char *s);
/* wave185: xlang_rel_o_path_from_argv0 pure cold twin below (forward for push_obj). */
const char *xlang_rel_o_path_from_argv0(const char *argv0, const char *rel);
void link_diag_ld_debug_push(const char *rel, const char *stage, const char *path);
/* Cap residual used by wave149 push_glue cold twin (mega always provides). */
int link_abi_call_ensure_argv0(void *ensure_fn, const char *link_argv0);
/* Cap residual used by wave150 push_minimal cold twin (mega always provides). */
/* wave163: panic_o_path is pure in this cold twin (forward decl for push_minimal). */
const char *xlang_runtime_asm_io_stubs_o_path(const char *argv0);
const char *xlang_runtime_process_argv_o_path(const char *argv0);
const char *xlang_runtime_panic_o_path(const char *argv0);
/* wave253: user-domain residual face companion (forward decl for push_minimal). */
const char *xlang_runtime_link_abi_user_env_o_path(const char *argv0);
/* Cap residual used by wave151 append_user_extra cold twin (mega always provides). */
int link_abi_user_extra_o_count(void);
const char *link_abi_user_extra_o_at(int i);
int link_abi_path_readable(const char *path);
/* Cap residual used by wave160 compiler_o_path_copy / wave162 repo_root cold twin (mega always provides). */
int xlang_resolve_compiler_dir(const char *argv0, char *out_dir, size_t out_dir_sz);
/* Cap residual used by wave163 panic_o_path cold twin (path_io / libc). */
const char *xlang_runtime_o_realpath_if_exists(const char *path, char *resolved);
char *getcwd(char *buf, size_t size);
/* Cap residual used by wave164/165/166 crt0_user / freestanding_io / async_scheduler_o_path
 * cold twin (POSIX realpath; already declared as link_abi_realpath_cap above for wave146). */
/* Pure peer defined earlier in this cold twin (wave116); declared for clarity. */
const char *xlang_asm_ld_try_under_lib_roots(const char *rel, const char **lib_roots, int n_lib_roots, void *bank);
int32_t link_abi_asm_ld_argv_has_obj(const char **argv, int la, const char *path);
void link_abi_asm_ld_argv_push_stable(void *bank, const char **argv, int *la, int max_la, const char *p);
int link_abi_asm_ld_push_obj(const char *primary, const char *link_argv0, const char *rel,
    const char **lib_roots, int n_lib_roots, void *bank, const char **argv, int *la, int max_la,
    int *flag_out);

#ifndef XLANG_LABI_PATH_PURE_FROM_X

int32_t labi_suffix_eq2(uint8_t *s, int32_t n, uint8_t a0, uint8_t a1) {
  if (n < 2) {
    return 0;
  }
  if (s[n - 2] != a0) {
    return 0;
  }
  if (s[n - 1] != a1) {
    return 0;
  }
  return 1;
}

int32_t labi_suffix_eq4(uint8_t *s, int32_t n, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3) {
  if (n < 4) {
    return 0;
  }
  if (s[n - 4] != a0) {
    return 0;
  }
  if (s[n - 3] != a1) {
    return 0;
  }
  if (s[n - 2] != a2) {
    return 0;
  }
  if (s[n - 1] != a3) {
    return 0;
  }
  return 1;
}

int32_t link_abi_ld_argv_entry_is_obj(uint8_t *s) {
  int32_t n = 0;
  if (s == ((uint8_t *)(0))) {
    return 0;
  }
  if (s[0] == 0) {
    return 0;
  }
  while (s[n] != 0) {
    n = n + 1;
  }
  if (labi_suffix_eq2(s, n, 46, 111) != 0) {
    return 1;
  }
  if (labi_suffix_eq4(s, n, 46, 111, 98, 106) != 0) {
    return 1;
  }
  return 0;
}

int32_t xlang_output_is_elf_o(uint8_t *path) {
  int32_t n = 0;
  if (path == ((uint8_t *)(0))) {
    return 0;
  }
  while (path[n] != 0) {
    n = n + 1;
  }
  if (labi_suffix_eq2(path, n, 46, 111) != 0) {
    return 1;
  }
  if (labi_suffix_eq2(path, n, 46, 79) != 0) {
    return 1;
  }
  if (labi_suffix_eq4(path, n, 46, 111, 98, 106) != 0) {
    return 1;
  }
  return 0;
}

int32_t xlang_output_want_exe(uint8_t *path) {
  int32_t n = 0;
  if (path == ((uint8_t *)(0))) {
    return 0;
  }
  if (path[0] == 0) {
    return 0;
  }
  while (path[n] != 0) {
    n = n + 1;
  }
  if (labi_suffix_eq2(path, n, 46, 111) != 0) {
    return 0;
  }
  if (labi_suffix_eq2(path, n, 46, 79) != 0) {
    return 0;
  }
  if (labi_suffix_eq2(path, n, 46, 115) != 0) {
    return 0;
  }
  if (labi_suffix_eq4(path, n, 46, 111, 98, 106) != 0) {
    return 0;
  }
  return 1;
}

int32_t xlang_path_has_sep(uint8_t *s) {
  if (s == ((uint8_t *)(0))) {
    return 0;
  }
  int32_t i = 0;
  while (s[i] != 0) {
    if (s[i] == 47) {
      return 1;
    }
    i = i + 1;
  }
  return 0;
}

uint8_t *xlang_path_last_sep(uint8_t *s) {
  if (s == ((uint8_t *)(0))) {
    return ((uint8_t *)(0));
  }
  int32_t last = 0;
  int32_t found = 0;
  int32_t i = 0;
  while (s[i] != 0) {
    if (s[i] == 47) {
      last = i;
      found = 1;
    }
    i = i + 1;
  }
  if (found == 0) {
    return ((uint8_t *)(0));
  }
  size_t base = ((size_t)(s));
  return ((uint8_t *)((base + ((size_t)(last)))));
}

/* wave114 cold twin: lib-root pointer usable (null / low-tag / empty). */
int32_t xlang_asm_ld_lib_root_ptr_usable(uint8_t *p) {
  if (p == ((uint8_t *)(0))) {
    return 0;
  }
  if (((size_t)(p)) < ((size_t)(4096))) {
    return 0;
  }
  if (p[0] == 0) {
    return 0;
  }
  return 1;
}

/* wave115 cold twin: default lib-root (XLANG_LIB or "."). Cap residual: link_abi_getenv (wave223). */
void xlang_asm_ld_lib_root_default(uint8_t *root_buf) {
  const char *def;
  root_buf[0] = (uint8_t)'.';
  root_buf[1] = 0;
  def = link_abi_getenv("XLANG_LIB");
  if (xlang_asm_ld_lib_root_ptr_usable((uint8_t *)def) == 0) {
    return;
  }
  strncpy((char *)root_buf, def, 511);
  root_buf[511] = 0;
}

/* wave116 cold twin: try rel under each lib root (pure join; Cap skip+bank). */
const char *xlang_asm_ld_try_under_lib_roots(const char *rel, const char **lib_roots, int n_lib_roots, void *bank) {
  int i;
  char tmp[4096];
  size_t rel_n;
  if (!rel || (uintptr_t)rel < 4096u)
    return NULL;
  if (!rel[0] || !bank || !lib_roots || (uintptr_t)lib_roots < 4096u || n_lib_roots <= 0)
    return NULL;
  rel_n = strlen(rel);
  for (i = 0; i < n_lib_roots && i < 24; i++) {
    size_t rn;
    size_t j;
    const char *root = lib_roots[i];
    if (!root || (uintptr_t)root < 4096u)
      continue;
    if (!root[0])
      continue;
    rn = strlen(root);
    while (rn > 1 && root[rn - 1] == '/')
      rn--;
    if (rn + 2 + rel_n >= sizeof(tmp))
      continue;
    if (rn > 0) {
      for (j = 0; j < rn; j++)
        tmp[j] = root[j];
      tmp[rn] = '/';
      for (j = 0; j <= rel_n; j++)
        tmp[rn + 1 + j] = rel[j];
    } else {
      for (j = 0; j <= rel_n; j++)
        tmp[j] = rel[j];
    }
    if (!asm_link_obj_skip_missing(tmp))
      continue;
    return xlang_asm_ld_bank_push(bank, tmp);
  }
  return NULL;
}

/* Pure audit: number of L0 path-pure public gates in this slice. */
/* wave146: argv has_obj pure orch (cold twin ≡ .x; Cap residual realpath_cap). */
int32_t link_abi_asm_ld_argv_has_obj(const char **argv, int la, const char *path) {
  int k;
  char abs_new[4096];
  char abs_exist[4096];
  const char *use_new;
  const char *rn;
  if (!argv || la <= 0 || !path || !path[0])
    return 0;
  use_new = path;
  rn = link_abi_realpath_cap(path, abs_new);
  if (rn)
    use_new = rn;
  for (k = 0; k < la; k++) {
    const char *exist = argv[k];
    const char *re;
    if (!exist || !exist[0])
      continue;
    if (strcmp(exist, path) == 0 || strcmp(exist, use_new) == 0)
      return 1;
    re = link_abi_realpath_cap(exist, abs_exist);
    if (re && strcmp(re, use_new) == 0)
      return 1;
  }
  return 0;
}

/* wave147: argv push_stable pure orch (cold twin ≡ .x; Cap residual bank_push). */
void link_abi_asm_ld_argv_push_stable(void *bank, const char **argv, int *la, int max_la,
    const char *p) {
  const char *use_p;
  int cur;
  if (!p || !p[0] || !la)
    return;
  cur = *la;
  if (cur >= max_la - 1)
    return;
  use_p = p;
  if (bank) {
    const char *bp = xlang_asm_ld_bank_push(bank, p);
    if (bp)
      use_p = bp;
  }
  if (link_abi_asm_ld_argv_has_obj(argv, cur, use_p))
    return;
  if (!argv)
    return;
  argv[cur] = use_p;
  *la = cur + 1;
}

/* wave148: push_obj pure orch (cold twin ≡ .x; Cap residual skip/rel/bank/diag). */
int link_abi_asm_ld_push_obj(const char *primary, const char *link_argv0, const char *rel,
    const char **lib_roots, int n_lib_roots, void *bank, const char **argv, int *la, int max_la,
    int *flag_out) {
  const char *p = NULL;
  int debug_runtime_obj = 0;
  int before;
  if (!la || *la >= max_la - 1)
    return 0;
  if (rel && (strcmp(rel, "compiler/runtime_asm_io_stubs.o") == 0
          || strcmp(rel, "compiler/runtime_process_argv.o") == 0))
    debug_runtime_obj = 1;
  /* wave223 G.7: link_abi_getenv (not raw getenv). */
  if (debug_runtime_obj && link_abi_getenv("XLANG_DEBUG_LD"))
    link_diag_ld_debug_push(rel, "primary", primary ? primary : "(null)");
  if (primary && primary[0])
    p = asm_link_obj_skip_missing(primary);
  if (debug_runtime_obj && link_abi_getenv("XLANG_DEBUG_LD"))
    link_diag_ld_debug_push(rel, "after-primary", p ? p : "(null)");
  if (!p && rel && rel[0])
    p = asm_link_obj_skip_missing(xlang_rel_o_path_from_argv0(link_argv0, rel));
  if (!p && bank && rel && rel[0])
    p = xlang_asm_ld_try_under_lib_roots(rel, lib_roots, n_lib_roots, bank);
  if (!p)
    return 0;
  if (bank) {
    const char *bp = xlang_asm_ld_bank_push(bank, p);
    if (bp)
      p = bp;
    else
      return 0;
  }
  if (debug_runtime_obj && link_abi_getenv("XLANG_DEBUG_LD"))
    link_diag_ld_debug_push(rel, "final", p ? p : "(null)");
  /* Single-authority append: wave147 push_stable bank=null after hard bank. */
  before = *la;
  link_abi_asm_ld_argv_push_stable(NULL, argv, la, max_la, p);
  if (*la <= before)
    return 0;
  if (flag_out)
    *flag_out = 1;
  return 1;
}

/* wave149: push_glue_after_std pure orch (cold twin ≡ .x; Cap residual call_ensure). */
void link_abi_asm_ld_push_glue_after_std(int have_std, int (*ensure_fn)(const char *argv0),
    const char *glue_primary, const char *link_argv0, const char *glue_rel,
    const char **lib_roots, int n_lib_roots, void *bank, const char **argv, int *la, int max_la) {
  if (!have_std)
    return;
  if (ensure_fn) {
    if (link_abi_call_ensure_argv0((void *)ensure_fn, link_argv0) != 0)
      return;
  }
  (void)link_abi_asm_ld_push_obj(glue_primary, link_argv0, glue_rel, lib_roots, n_lib_roots,
      bank, argv, la, max_la, NULL);
}

/* wave150: push_minimal_runtime_objs pure orch (cold twin ≡ .x; Cap residual *_o_path). */
void link_abi_asm_ld_push_minimal_runtime_objs(const char *link_argv0, const char **lib_roots,
    int n_lib_roots, void *bank, const char **argv, int *la, int max_la) {
  const char *io_p = xlang_runtime_asm_io_stubs_o_path(link_argv0);
  const char *proc_p = xlang_runtime_process_argv_o_path(link_argv0);
  const char *panic_p = xlang_runtime_panic_o_path(link_argv0);
  (void)link_abi_asm_ld_push_obj(io_p, link_argv0, "compiler/runtime_asm_io_stubs.o",
      lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
  (void)link_abi_asm_ld_push_obj(proc_p, link_argv0, "compiler/runtime_process_argv.o",
      lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
  (void)link_abi_asm_ld_push_obj(panic_p, link_argv0, "compiler/runtime_panic.o",
      lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
  /* wave253: companion user-domain face (weak; residual declare-only; panic C strong wins). */
  {
    const char *ue_p = xlang_runtime_link_abi_user_env_o_path(link_argv0);
    (void)link_abi_asm_ld_push_obj(ue_p, link_argv0, "compiler/runtime_link_abi_user_env.o",
        lib_roots, n_lib_roots, bank, argv, la, max_la, NULL);
  }
}

/* wave151: append_user_extra_o_files pure orch (cold twin ≡ .x; Cap residual table+access). */
void xlang_asm_ld_append_user_extra_o_files(const char **argv, int *la, int max_la) {
  int n;
  int ui;
  if (!argv || !la)
    return;
  n = link_abi_user_extra_o_count();
  for (ui = 0; ui < n; ui++) {
    const char *p;
    if (*la >= max_la - 1)
      break;
    p = link_abi_user_extra_o_at(ui);
    if (!p || !p[0])
      continue;
    if (!link_abi_path_readable(p))
      continue;
    /* G.7: skip extra .o already on argv (auto companion / earlier extra). */
    if (link_abi_asm_ld_argv_has_obj(argv, *la, p))
      continue;
    argv[(*la)++] = p;
  }
}

/* wave160: compiler_o_path_copy pure orch (cold twin ≡ .x; Cap residual resolve). */
int xlang_runtime_compiler_o_path_copy(const char *argv0, const char *leaf, char *out, size_t out_sz) {
  char comp_dir[4096];
  int dn;
  int ln;
  int i;
  int k;
  size_t need;
  if (!out || out_sz == 0 || !leaf || !leaf[0])
    return -1;
  out[0] = '\0';
  if (xlang_resolve_compiler_dir(argv0, comp_dir, sizeof comp_dir) != 0)
    return -1;
  dn = 0;
  while (comp_dir[dn] != 0)
    dn = dn + 1;
  ln = 0;
  while (leaf[ln] != 0)
    ln = ln + 1;
  need = (size_t)dn + 1u + (size_t)ln;
  if (need >= out_sz) {
    out[0] = '\0';
    return -1;
  }
  for (i = 0; i < dn; i++)
    out[i] = comp_dir[i];
  out[dn] = '/';
  for (k = 0; k <= ln; k++)
    out[dn + 1 + k] = leaf[k];
  return 0;
}

/* wave162: repo_root pure orch (cold twin ≡ .x; Cap residual resolve + rel_o_path). */
static char g_labi_repo_root_buf[512];

const char *xlang_repo_root_from_argv0(const char *argv0) {
  char comp[4096];
  int n;
  int i;
  int pn;
  int j;
  int k;
  char *last;
  const char *proc_o;
  g_labi_repo_root_buf[0] = '\0';
  if (xlang_resolve_compiler_dir(argv0, comp, sizeof comp) == 0 && comp[0]) {
    n = 0;
    while (comp[n] != 0)
      n = n + 1;
    if (n < 512) {
      for (i = 0; i <= n; i++)
        g_labi_repo_root_buf[i] = comp[i];
      last = (char *)xlang_path_last_sep((uint8_t *)g_labi_repo_root_buf);
      if (last && last != g_labi_repo_root_buf) {
        *last = '\0';
        return g_labi_repo_root_buf;
      }
      g_labi_repo_root_buf[0] = '\0';
    }
  }
  proc_o = xlang_rel_o_path_from_argv0(argv0, "std/process/process.o");
  if (!proc_o || !proc_o[0])
    return g_labi_repo_root_buf;
  pn = 0;
  while (proc_o[pn] != 0)
    pn = pn + 1;
  if (pn >= 512)
    return g_labi_repo_root_buf;
  for (j = 0; j <= pn; j++)
    g_labi_repo_root_buf[j] = proc_o[j];
  for (k = 0; k < 3; k++) {
    last = (char *)xlang_path_last_sep((uint8_t *)g_labi_repo_root_buf);
    if (!last || last == g_labi_repo_root_buf)
      break;
    *last = '\0';
  }
  return g_labi_repo_root_buf;
}

/* wave163: panic_o_path pure orch (cold twin ≡ .x; Cap residual realpath+getcwd+skip). */
static char g_labi_panic_o_path_buf[512];
static char g_labi_panic_o_path_resolved[4096];

const char *xlang_runtime_panic_o_path(const char *argv0) {
  const char *hit;
  char cwd[512];
  int i;
  int last_sep_i;
  int n;
  int j;
  int k;
  const char *sm;
  g_labi_panic_o_path_buf[0] = '\0';
  g_labi_panic_o_path_resolved[0] = '\0';
  hit = xlang_runtime_o_realpath_if_exists("runtime_panic.o", g_labi_panic_o_path_resolved);
  if (hit)
    return hit;
  hit = xlang_runtime_o_realpath_if_exists("compiler/runtime_panic.o", g_labi_panic_o_path_resolved);
  if (hit)
    return hit;
  if (getcwd(cwd, 488) != NULL) {
    int L = 0;
    while (cwd[L] != 0)
      L = L + 1;
    if (L + 24 < 512) {
      const char *suf = "/compiler/runtime_panic.o";
      int si = 0;
      while (si <= 24) {
        cwd[L + si] = suf[si];
        si = si + 1;
      }
      hit = xlang_runtime_o_realpath_if_exists(cwd, g_labi_panic_o_path_resolved);
      if (hit)
        return hit;
    }
  }
  if (argv0 && argv0[0]) {
    i = 0;
    last_sep_i = -1;
    while (argv0[i] != 0) {
      if ((uint8_t)argv0[i] == 47)
        last_sep_i = i;
      i = i + 1;
    }
    n = 0;
    if (last_sep_i >= 0) {
      if (last_sep_i >= 512 - 20)
        return g_labi_panic_o_path_buf;
      for (j = 0; j < last_sep_i; j++)
        g_labi_panic_o_path_buf[j] = argv0[j];
      g_labi_panic_o_path_buf[last_sep_i] = '\0';
      n = last_sep_i;
    } else {
      g_labi_panic_o_path_buf[0] = '.';
      g_labi_panic_o_path_buf[1] = '\0';
      n = 1;
    }
    if (n + 18 < 512) {
      const char *leaf = "/runtime_panic.o";
      k = 0;
      while (leaf[k] != 0) {
        g_labi_panic_o_path_buf[n + k] = leaf[k];
        k = k + 1;
      }
      g_labi_panic_o_path_buf[n + k] = '\0';
      hit = xlang_runtime_o_realpath_if_exists(g_labi_panic_o_path_buf, g_labi_panic_o_path_resolved);
      if (hit)
        return hit;
      sm = asm_link_obj_skip_missing(g_labi_panic_o_path_buf);
      if (sm)
        return g_labi_panic_o_path_buf;
    }
  }
  return g_labi_panic_o_path_buf;
}

/* wave164: crt0_user_o_path pure orch (cold twin ≡ .x; Cap residual realpath_cap+getcwd). */
static char g_labi_crt0_user_o_path_buf[512];
static char g_labi_crt0_user_o_path_resolved[4096];

const char *xlang_crt0_user_o_path(const char *argv0) {
  const char *hit;
  char cwd[512];
  int i;
  int last_sep_i;
  int n;
  int j;
  int k;
  g_labi_crt0_user_o_path_buf[0] = '\0';
  g_labi_crt0_user_o_path_resolved[0] = '\0';
  hit = link_abi_realpath_cap("compiler/crt0_user.o", g_labi_crt0_user_o_path_resolved);
  if (hit)
    return hit;
  if (getcwd(cwd, 490) != NULL) {
    int L = 0;
    while (cwd[L] != 0)
      L = L + 1;
    if (L + 21 < 512) {
      const char *suf = "/compiler/crt0_user.o";
      int si = 0;
      while (si <= 21) {
        cwd[L + si] = suf[si];
        si = si + 1;
      }
      hit = link_abi_realpath_cap(cwd, g_labi_crt0_user_o_path_resolved);
      if (hit)
        return hit;
    }
  }
  if (argv0 && argv0[0]) {
    i = 0;
    last_sep_i = -1;
    while (argv0[i] != 0) {
      if ((uint8_t)argv0[i] == 47)
        last_sep_i = i;
      i = i + 1;
    }
    n = 0;
    if (last_sep_i >= 0) {
      if (last_sep_i >= 512 - 16)
        return g_labi_crt0_user_o_path_buf;
      for (j = 0; j < last_sep_i; j++)
        g_labi_crt0_user_o_path_buf[j] = argv0[j];
      g_labi_crt0_user_o_path_buf[last_sep_i] = '\0';
      n = last_sep_i;
    } else {
      g_labi_crt0_user_o_path_buf[0] = '.';
      g_labi_crt0_user_o_path_buf[1] = '\0';
      n = 1;
    }
    if (n + 14 < 512) {
      const char *leaf = "/crt0_user.o";
      k = 0;
      while (leaf[k] != 0) {
        g_labi_crt0_user_o_path_buf[n + k] = leaf[k];
        k = k + 1;
      }
      g_labi_crt0_user_o_path_buf[n + k] = '\0';
      hit = link_abi_realpath_cap(g_labi_crt0_user_o_path_buf, g_labi_crt0_user_o_path_resolved);
      if (hit)
        return hit;
      return g_labi_crt0_user_o_path_buf;
    }
  }
  return g_labi_crt0_user_o_path_buf;
}

/* wave165: freestanding_io_o_path pure orch (cold twin ≡ .x; Cap residual realpath_cap+getcwd). */
static char g_labi_freestanding_io_o_path_buf[512];
static char g_labi_freestanding_io_o_path_resolved[4096];

const char *xlang_freestanding_io_o_path(const char *argv0) {
  const char *hit;
  char cwd[512];
  int i;
  int last_sep_i;
  int n;
  int j;
  int k;
  g_labi_freestanding_io_o_path_buf[0] = '\0';
  g_labi_freestanding_io_o_path_resolved[0] = '\0';
  hit = link_abi_realpath_cap("compiler/freestanding_io.o", g_labi_freestanding_io_o_path_resolved);
  if (hit)
    return hit;
  if (getcwd(cwd, 484) != NULL) {
    int L = 0;
    while (cwd[L] != 0)
      L = L + 1;
    if (L + 27 < 512) {
      const char *suf = "/compiler/freestanding_io.o";
      int si = 0;
      while (si <= 27) {
        cwd[L + si] = suf[si];
        si = si + 1;
      }
      hit = link_abi_realpath_cap(cwd, g_labi_freestanding_io_o_path_resolved);
      if (hit)
        return hit;
    }
  }
  if (argv0 && argv0[0]) {
    i = 0;
    last_sep_i = -1;
    while (argv0[i] != 0) {
      if ((uint8_t)argv0[i] == 47)
        last_sep_i = i;
      i = i + 1;
    }
    n = 0;
    if (last_sep_i >= 0) {
      if (last_sep_i >= 512 - 20)
        return g_labi_freestanding_io_o_path_buf;
      for (j = 0; j < last_sep_i; j++)
        g_labi_freestanding_io_o_path_buf[j] = argv0[j];
      g_labi_freestanding_io_o_path_buf[last_sep_i] = '\0';
      n = last_sep_i;
    } else {
      g_labi_freestanding_io_o_path_buf[0] = '.';
      g_labi_freestanding_io_o_path_buf[1] = '\0';
      n = 1;
    }
    if (n + 18 < 512) {
      const char *leaf = "/freestanding_io.o";
      k = 0;
      while (leaf[k] != 0) {
        g_labi_freestanding_io_o_path_buf[n + k] = leaf[k];
        k = k + 1;
      }
      g_labi_freestanding_io_o_path_buf[n + k] = '\0';
      hit = link_abi_realpath_cap(g_labi_freestanding_io_o_path_buf, g_labi_freestanding_io_o_path_resolved);
      if (hit)
        return hit;
      return g_labi_freestanding_io_o_path_buf;
    }
  }
  return g_labi_freestanding_io_o_path_buf;
}

/* wave166: async_scheduler_o_path pure orch (cold twin ≡ .x; Cap residual realpath_cap+getcwd).
 * Step3: realpath(argv0) then parent + /../std/async/scheduler.o (≠ freestanding leaf join). */
static char g_labi_async_scheduler_o_path_buf[4096];
static char g_labi_async_scheduler_o_path_resolved[4096];

const char *xlang_std_async_scheduler_o_path(const char *argv0) {
  const char *hit;
  const char *rp;
  char cwd[512];
  int i;
  int last_sep_i;
  int n;
  int k;
  g_labi_async_scheduler_o_path_buf[0] = '\0';
  g_labi_async_scheduler_o_path_resolved[0] = '\0';
  hit = link_abi_realpath_cap("std/async/scheduler.o", g_labi_async_scheduler_o_path_resolved);
  if (hit)
    return hit;
  if (getcwd(cwd, 486) != NULL) {
    int L = 0;
    while (cwd[L] != 0)
      L = L + 1;
    if (L + 26 <= 512) {
      const char *suf = "/std/async/scheduler.o";
      int si = 0;
      while (si <= 22) {
        cwd[L + si] = suf[si];
        si = si + 1;
      }
      hit = link_abi_realpath_cap(cwd, g_labi_async_scheduler_o_path_resolved);
      if (hit)
        return hit;
    }
  }
  if (argv0 && argv0[0]) {
    rp = link_abi_realpath_cap(argv0, g_labi_async_scheduler_o_path_buf);
    if (rp) {
      i = 0;
      last_sep_i = -1;
      while (g_labi_async_scheduler_o_path_buf[i] != 0) {
        if ((uint8_t)g_labi_async_scheduler_o_path_buf[i] == 47)
          last_sep_i = i;
        i = i + 1;
      }
      if (last_sep_i >= 0) {
        if (last_sep_i + 26 < 4096) {
          g_labi_async_scheduler_o_path_buf[last_sep_i] = '\0';
          n = last_sep_i;
          {
            const char *leaf = "/../std/async/scheduler.o";
            k = 0;
            while (leaf[k] != 0) {
              g_labi_async_scheduler_o_path_buf[n + k] = leaf[k];
              k = k + 1;
            }
            g_labi_async_scheduler_o_path_buf[n + k] = '\0';
          }
          hit = link_abi_realpath_cap(g_labi_async_scheduler_o_path_buf, g_labi_async_scheduler_o_path_resolved);
          if (hit)
            return hit;
        }
      }
    }
  }
  return g_labi_async_scheduler_o_path_buf;
}

/* wave180: scheduler_o_for_task_link pure orch (cold twin ≡ .x;
 * Cap residual path_readable + realpath_cap). */
static char g_labi_sched_for_task_derived[4096];
static char g_labi_sched_for_task_cwd[4096];

const char *scheduler_o_for_task_link(const char *task_o, const char *explicit_scheduler) {
  int n;
  int ci;
  int pos;
  int i;
  int j;
  int ok;
  int new_n;
  int si;
  int k;
  int readable;
  const char *from;
  const char *to;
  const char *hit;
  int from_len;
  int to_len;
  int delta;
  if (explicit_scheduler && explicit_scheduler[0])
    return explicit_scheduler;
  if (!task_o || !task_o[0])
    return NULL;
  n = 0;
  while (task_o[n] != 0)
    n = n + 1;
  if (n >= 4096)
    return NULL;
  ci = 0;
  while (ci <= n) {
    g_labi_sched_for_task_derived[ci] = task_o[ci];
    ci = ci + 1;
  }
  from = "std/task/task.o";
  from_len = 15;
  to = "std/async/scheduler.o";
  to_len = 22;
  delta = 7;
  pos = -1;
  i = 0;
  while (i + from_len <= n) {
    if (pos < 0) {
      j = 0;
      ok = 1;
      while (j < from_len) {
        if (ok != 0) {
          if ((uint8_t)g_labi_sched_for_task_derived[i + j] != (uint8_t)from[j])
            ok = 0;
        }
        j = j + 1;
      }
      if (ok != 0)
        pos = i;
    }
    i = i + 1;
  }
  if (pos >= 0) {
    new_n = n + delta;
    if (new_n < 4096) {
      si = n;
      while (si >= pos + from_len) {
        g_labi_sched_for_task_derived[si + delta] = g_labi_sched_for_task_derived[si];
        si = si - 1;
      }
      k = 0;
      while (k < to_len) {
        g_labi_sched_for_task_derived[pos + k] = to[k];
        k = k + 1;
      }
      readable = link_abi_path_readable(g_labi_sched_for_task_derived);
      if (readable != 0)
        return g_labi_sched_for_task_derived;
    }
  }
  g_labi_sched_for_task_cwd[0] = '\0';
  hit = link_abi_realpath_cap("std/async/scheduler.o", g_labi_sched_for_task_cwd);
  if (hit)
    return hit;
  return NULL;
}

/* wave181: bootstrap_nostdlib_stubs_o_path pure orch (cold twin ≡ .x;
 * Cap residual realpath_cap + xlang_resolve_compiler_dir). */
static char g_labi_bootstrap_nostdlib_stubs_o_path_buf[4096];
static char g_labi_bootstrap_nostdlib_stubs_o_path_resolved[4096];

const char *xlang_bootstrap_nostdlib_stubs_o_path(const char *argv0) {
  const char *hit;
  char comp[4096];
  int rc;
  int dn;
  int ln;
  int i;
  int k;
  const char *leaf;
  g_labi_bootstrap_nostdlib_stubs_o_path_buf[0] = '\0';
  g_labi_bootstrap_nostdlib_stubs_o_path_resolved[0] = '\0';
  hit = link_abi_realpath_cap("compiler/src/asm/bootstrap_nostdlib_stubs.o",
                              g_labi_bootstrap_nostdlib_stubs_o_path_resolved);
  if (hit)
    return hit;
  rc = xlang_resolve_compiler_dir(argv0, comp, sizeof comp);
  if (rc == 0) {
    dn = 0;
    while (comp[dn] != 0)
      dn = dn + 1;
    leaf = "src/asm/bootstrap_nostdlib_stubs.o";
    ln = 0;
    while (leaf[ln] != 0)
      ln = ln + 1;
    if (dn + 1 + ln < 4096) {
      i = 0;
      while (i < dn) {
        g_labi_bootstrap_nostdlib_stubs_o_path_buf[i] = comp[i];
        i = i + 1;
      }
      g_labi_bootstrap_nostdlib_stubs_o_path_buf[dn] = '/';
      k = 0;
      while (k <= ln) {
        g_labi_bootstrap_nostdlib_stubs_o_path_buf[dn + 1 + k] = leaf[k];
        k = k + 1;
      }
      hit = link_abi_realpath_cap(g_labi_bootstrap_nostdlib_stubs_o_path_buf,
                                  g_labi_bootstrap_nostdlib_stubs_o_path_resolved);
      if (hit)
        return hit;
      return g_labi_bootstrap_nostdlib_stubs_o_path_buf;
    }
  }
  return g_labi_bootstrap_nostdlib_stubs_o_path_buf;
}

/* wave183: thin runtime_*_o_path pure orch (cold twin ≡ .x). */
static char g_labi_asm_io_stubs_o_path_buf[4096];
static char g_labi_process_argv_o_path_buf[4096];
static char g_labi_process_os_glue_o_path_buf[4096];
static char g_labi_test_fn_invoke_o_path_buf[4096];
static char g_labi_random_fill_o_path_buf[4096];
static char g_labi_compress_zlib_glue_o_path_buf[4096];
static char g_labi_heap_user_o_path_buf[4096];
static char g_labi_time_os_o_path_buf[4096];
static char g_labi_queue_contention_o_path_buf[4096];
static char g_labi_dynlib_os_o_path_buf[4096];
static char g_labi_env_os_o_path_buf[4096];
static char g_labi_link_abi_user_env_o_path_buf[4096];
static char g_labi_backtrace_platform_o_path_buf[4096];
static char g_labi_log_os_o_path_buf[4096];
static char g_labi_math_libm_o_path_buf[4096];
static char g_labi_atomic_glue_o_path_buf[4096];
static char g_labi_channel_glue_o_path_buf[4096];
static char g_labi_net_udp_batch_o_path_buf[4096];
static char g_labi_net_workers_o_path_buf[4096];
static char g_labi_sync_os_o_path_buf[4096];
static char g_labi_sync_lock_diag_tls_o_path_buf[4096];
static char g_labi_thread_glue_o_path_buf[4096];
static char g_labi_scheduler_glue_o_path_buf[4096];
static char g_labi_http_glue_o_path_buf[4096];
static char g_labi_tls_mbedtls_bio_o_path_buf[4096];
static char g_labi_kv_mmap_glue_o_path_buf[4096];
static char g_labi_arrow_simd_glue_o_path_buf[4096];
static char g_labi_sqlite_glue_o_path_buf[4096];
static char g_labi_crypto_inc_glue_o_path_buf[4096];
static char g_labi_ed25519_ref10_glue_o_path_buf[4096];
/* wave184: durable empty C string (≡ mega static char buf[1]). */
static char g_labi_empty_cstr_buf[1];

const char *xlang_runtime_asm_io_stubs_o_path(const char *argv0) {
  g_labi_asm_io_stubs_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_asm_io_stubs.o", g_labi_asm_io_stubs_o_path_buf, sizeof g_labi_asm_io_stubs_o_path_buf) != 0)
    g_labi_asm_io_stubs_o_path_buf[0] = '\0';
  return g_labi_asm_io_stubs_o_path_buf;
}

const char *xlang_runtime_process_argv_o_path(const char *argv0) {
  g_labi_process_argv_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_process_argv.o", g_labi_process_argv_o_path_buf, sizeof g_labi_process_argv_o_path_buf) != 0)
    g_labi_process_argv_o_path_buf[0] = '\0';
  return g_labi_process_argv_o_path_buf;
}

const char *xlang_runtime_process_os_glue_o_path(const char *argv0) {
  g_labi_process_os_glue_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_process_os_glue.o", g_labi_process_os_glue_o_path_buf, sizeof g_labi_process_os_glue_o_path_buf) != 0)
    g_labi_process_os_glue_o_path_buf[0] = '\0';
  return g_labi_process_os_glue_o_path_buf;
}

const char *xlang_runtime_test_fn_invoke_o_path(const char *argv0) {
  g_labi_test_fn_invoke_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_test_fn_invoke.o", g_labi_test_fn_invoke_o_path_buf, sizeof g_labi_test_fn_invoke_o_path_buf) != 0)
    g_labi_test_fn_invoke_o_path_buf[0] = '\0';
  return g_labi_test_fn_invoke_o_path_buf;
}

const char *xlang_runtime_random_fill_o_path(const char *argv0) {
  g_labi_random_fill_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_random_fill.o", g_labi_random_fill_o_path_buf, sizeof g_labi_random_fill_o_path_buf) != 0)
    g_labi_random_fill_o_path_buf[0] = '\0';
  return g_labi_random_fill_o_path_buf;
}

const char *xlang_runtime_compress_zlib_glue_o_path(const char *argv0) {
  g_labi_compress_zlib_glue_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_compress_zlib_glue.o", g_labi_compress_zlib_glue_o_path_buf, sizeof g_labi_compress_zlib_glue_o_path_buf) != 0)
    g_labi_compress_zlib_glue_o_path_buf[0] = '\0';
  return g_labi_compress_zlib_glue_o_path_buf;
}

const char *xlang_runtime_heap_user_o_path(const char *argv0) {
  g_labi_heap_user_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_heap_user.o", g_labi_heap_user_o_path_buf, sizeof g_labi_heap_user_o_path_buf) != 0)
    g_labi_heap_user_o_path_buf[0] = '\0';
  return g_labi_heap_user_o_path_buf;
}

const char *xlang_runtime_time_os_o_path(const char *argv0) {
  g_labi_time_os_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_time_os.o", g_labi_time_os_o_path_buf, sizeof g_labi_time_os_o_path_buf) != 0)
    g_labi_time_os_o_path_buf[0] = '\0';
  return g_labi_time_os_o_path_buf;
}

const char *xlang_runtime_queue_contention_o_path(const char *argv0) {
  g_labi_queue_contention_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_queue_contention.o", g_labi_queue_contention_o_path_buf, sizeof g_labi_queue_contention_o_path_buf) != 0)
    g_labi_queue_contention_o_path_buf[0] = '\0';
  return g_labi_queue_contention_o_path_buf;
}

const char *xlang_runtime_dynlib_os_o_path(const char *argv0) {
  g_labi_dynlib_os_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_dynlib_os.o", g_labi_dynlib_os_o_path_buf, sizeof g_labi_dynlib_os_o_path_buf) != 0)
    g_labi_dynlib_os_o_path_buf[0] = '\0';
  return g_labi_dynlib_os_o_path_buf;
}

const char *xlang_runtime_env_os_o_path(const char *argv0) {
  g_labi_env_os_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_env_os.o", g_labi_env_os_o_path_buf, sizeof g_labi_env_os_o_path_buf) != 0)
    g_labi_env_os_o_path_buf[0] = '\0';
  return g_labi_env_os_o_path_buf;
}

/* wave253: thin durable path for runtime_link_abi_user_env.o (companion face). */
const char *xlang_runtime_link_abi_user_env_o_path(const char *argv0) {
  g_labi_link_abi_user_env_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_link_abi_user_env.o", g_labi_link_abi_user_env_o_path_buf, sizeof g_labi_link_abi_user_env_o_path_buf) != 0)
    g_labi_link_abi_user_env_o_path_buf[0] = '\0';
  return g_labi_link_abi_user_env_o_path_buf;
}

const char *xlang_runtime_backtrace_platform_o_path(const char *argv0) {
  g_labi_backtrace_platform_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_backtrace_platform.o", g_labi_backtrace_platform_o_path_buf, sizeof g_labi_backtrace_platform_o_path_buf) != 0)
    g_labi_backtrace_platform_o_path_buf[0] = '\0';
  return g_labi_backtrace_platform_o_path_buf;
}

const char *xlang_runtime_log_os_o_path(const char *argv0) {
  g_labi_log_os_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_log_os.o", g_labi_log_os_o_path_buf, sizeof g_labi_log_os_o_path_buf) != 0)
    g_labi_log_os_o_path_buf[0] = '\0';
  return g_labi_log_os_o_path_buf;
}

const char *xlang_runtime_math_libm_o_path(const char *argv0) {
  g_labi_math_libm_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_math_libm.o", g_labi_math_libm_o_path_buf, sizeof g_labi_math_libm_o_path_buf) != 0)
    g_labi_math_libm_o_path_buf[0] = '\0';
  return g_labi_math_libm_o_path_buf;
}

const char *xlang_runtime_atomic_glue_o_path(const char *argv0) {
  g_labi_atomic_glue_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_atomic_glue.o", g_labi_atomic_glue_o_path_buf, sizeof g_labi_atomic_glue_o_path_buf) != 0)
    g_labi_atomic_glue_o_path_buf[0] = '\0';
  return g_labi_atomic_glue_o_path_buf;
}

const char *xlang_runtime_channel_glue_o_path(const char *argv0) {
  g_labi_channel_glue_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_channel_glue.o", g_labi_channel_glue_o_path_buf, sizeof g_labi_channel_glue_o_path_buf) != 0)
    g_labi_channel_glue_o_path_buf[0] = '\0';
  return g_labi_channel_glue_o_path_buf;
}

const char *xlang_runtime_net_udp_batch_o_path(const char *argv0) {
  g_labi_net_udp_batch_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_net_udp_batch.o", g_labi_net_udp_batch_o_path_buf, sizeof g_labi_net_udp_batch_o_path_buf) != 0)
    g_labi_net_udp_batch_o_path_buf[0] = '\0';
  return g_labi_net_udp_batch_o_path_buf;
}

const char *xlang_runtime_net_workers_o_path(const char *argv0) {
  g_labi_net_workers_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_net_workers.o", g_labi_net_workers_o_path_buf, sizeof g_labi_net_workers_o_path_buf) != 0)
    g_labi_net_workers_o_path_buf[0] = '\0';
  return g_labi_net_workers_o_path_buf;
}

const char *xlang_runtime_sync_os_o_path(const char *argv0) {
  g_labi_sync_os_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_sync_os.o", g_labi_sync_os_o_path_buf, sizeof g_labi_sync_os_o_path_buf) != 0)
    g_labi_sync_os_o_path_buf[0] = '\0';
  return g_labi_sync_os_o_path_buf;
}

const char *xlang_runtime_sync_lock_diag_tls_o_path(const char *argv0) {
  g_labi_sync_lock_diag_tls_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_sync_lock_diag_tls.o", g_labi_sync_lock_diag_tls_o_path_buf, sizeof g_labi_sync_lock_diag_tls_o_path_buf) != 0)
    g_labi_sync_lock_diag_tls_o_path_buf[0] = '\0';
  return g_labi_sync_lock_diag_tls_o_path_buf;
}

const char *xlang_runtime_thread_glue_o_path(const char *argv0) {
  g_labi_thread_glue_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_thread_glue.o", g_labi_thread_glue_o_path_buf, sizeof g_labi_thread_glue_o_path_buf) != 0)
    g_labi_thread_glue_o_path_buf[0] = '\0';
  return g_labi_thread_glue_o_path_buf;
}

const char *xlang_runtime_scheduler_glue_o_path(const char *argv0) {
  g_labi_scheduler_glue_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_scheduler_glue.o", g_labi_scheduler_glue_o_path_buf, sizeof g_labi_scheduler_glue_o_path_buf) != 0)
    g_labi_scheduler_glue_o_path_buf[0] = '\0';
  return g_labi_scheduler_glue_o_path_buf;
}

const char *xlang_runtime_http_glue_o_path(const char *argv0) {
  g_labi_http_glue_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_http_glue.o", g_labi_http_glue_o_path_buf, sizeof g_labi_http_glue_o_path_buf) != 0)
    g_labi_http_glue_o_path_buf[0] = '\0';
  return g_labi_http_glue_o_path_buf;
}

const char *xlang_runtime_tls_mbedtls_bio_o_path(const char *argv0) {
  g_labi_tls_mbedtls_bio_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_tls_mbedtls_bio.o", g_labi_tls_mbedtls_bio_o_path_buf, sizeof g_labi_tls_mbedtls_bio_o_path_buf) != 0)
    g_labi_tls_mbedtls_bio_o_path_buf[0] = '\0';
  return g_labi_tls_mbedtls_bio_o_path_buf;
}

const char *xlang_runtime_kv_mmap_glue_o_path(const char *argv0) {
  g_labi_kv_mmap_glue_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_kv_mmap_glue.o", g_labi_kv_mmap_glue_o_path_buf, sizeof g_labi_kv_mmap_glue_o_path_buf) != 0)
    g_labi_kv_mmap_glue_o_path_buf[0] = '\0';
  return g_labi_kv_mmap_glue_o_path_buf;
}

const char *xlang_runtime_arrow_simd_glue_o_path(const char *argv0) {
  g_labi_arrow_simd_glue_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_arrow_simd_glue.o", g_labi_arrow_simd_glue_o_path_buf, sizeof g_labi_arrow_simd_glue_o_path_buf) != 0)
    g_labi_arrow_simd_glue_o_path_buf[0] = '\0';
  return g_labi_arrow_simd_glue_o_path_buf;
}

const char *xlang_runtime_sqlite_glue_o_path(const char *argv0) {
  g_labi_sqlite_glue_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_sqlite_glue.o", g_labi_sqlite_glue_o_path_buf, sizeof g_labi_sqlite_glue_o_path_buf) != 0)
    g_labi_sqlite_glue_o_path_buf[0] = '\0';
  return g_labi_sqlite_glue_o_path_buf;
}

const char *xlang_runtime_crypto_inc_glue_o_path(const char *argv0) {
  g_labi_crypto_inc_glue_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_crypto_inc_glue.o", g_labi_crypto_inc_glue_o_path_buf, sizeof g_labi_crypto_inc_glue_o_path_buf) != 0)
    g_labi_crypto_inc_glue_o_path_buf[0] = '\0';
  return g_labi_crypto_inc_glue_o_path_buf;
}

const char *xlang_runtime_ed25519_ref10_glue_o_path(const char *argv0) {
  g_labi_ed25519_ref10_glue_o_path_buf[0] = '\0';
  if (xlang_runtime_compiler_o_path_copy(argv0, "runtime_ed25519_ref10_glue.o", g_labi_ed25519_ref10_glue_o_path_buf, sizeof g_labi_ed25519_ref10_glue_o_path_buf) != 0)
    g_labi_ed25519_ref10_glue_o_path_buf[0] = '\0';
  return g_labi_ed25519_ref10_glue_o_path_buf;
}

/* wave184 cold twin: durable empty C string. */
const char *xlang_empty_cstr(void) {
  g_labi_empty_cstr_buf[0] = '\0';
  return g_labi_empty_cstr_buf;
}

/* wave184 cold twin: retired std.io path → empty. */
const char *xlang_std_io_o_path(const char *argv0) {
  (void)argv0;
  return xlang_empty_cstr();
}

/* wave184 cold twin: retired std.compress path → empty. */
const char *xlang_std_compress_o_path(const char *argv0) {
  (void)argv0;
  return xlang_empty_cstr();
}

/* wave184 cold twin: effective link argv0 (Cap residual resolve + pure join). */
const char *xlang_asm_ld_effective_link_argv0(const char *link_argv0, char *syn_buf, size_t syn_sz) {
  char comp_dir[4096];
  size_t dn;
  size_t need;
  size_t i;
  if (link_argv0 && link_argv0[0])
    return link_argv0;
  if (!syn_buf || syn_sz == 0)
    return NULL;
  syn_buf[0] = '\0';
  if (xlang_resolve_compiler_dir(NULL, comp_dir, sizeof comp_dir) != 0)
    return NULL;
  dn = strlen(comp_dir);
  /* "%s/xlang" → dn + 1 + 4 + NUL; fail if need >= syn_sz (mega size_t). */
  need = dn + 1 + 4;
  if (need >= syn_sz) {
    syn_buf[0] = '\0';
    return NULL;
  }
  for (i = 0; i < dn; i++)
    syn_buf[i] = comp_dir[i];
  syn_buf[dn] = '/';
  syn_buf[dn + 1] = 's';
  syn_buf[dn + 2] = 'h';
  syn_buf[dn + 3] = 'u';
  syn_buf[dn + 4] = 'x';
  syn_buf[dn + 5] = '\0';
  return syn_buf;
}

/* wave185 cold twin: rel_o_path pure orch (Cap residual realpath_cap + getcwd + cstr_dup + skip).
 * Heap return per call (never static BSS) — matches mega multi-call independence invariant. */
const char *xlang_rel_o_path_from_argv0(const char *argv0, const char *rel) {
  char buf[512];
  char resolved[4096];
  char cwd[512];
  size_t rel_len;
  size_t L;
  size_t i;
  int last_sep_i;
  int n;
  const char *rp;
  const char *sm;
  buf[0] = resolved[0] = '\0';
  if (!rel || !rel[0])
    return link_abi_cstr_dup("");
  rel_len = strlen(rel);
  /* Step 1: realpath(rel). Cap residual realpath_cap (≡ mega realpath on POSIX). */
  rp = link_abi_realpath_cap(rel, resolved);
  if (rp)
    return link_abi_cstr_dup(rp);
  /* Step 2: getcwd + "/" + rel. mega: getcwd(cwd, sizeof(cwd)-2). */
  if (getcwd(cwd, sizeof(cwd) - 2) != NULL) {
    L = strlen(cwd);
    if (L + 1 + rel_len + 1 <= sizeof(cwd)) {
      cwd[L] = '/';
      memcpy(cwd + L + 1, rel, rel_len + 1);
      rp = link_abi_realpath_cap(cwd, resolved);
      if (rp)
        return link_abi_cstr_dup(rp);
    }
  }
  /* Step 3: argv0 parent + "/../" + rel. Pure last-sep index (POSIX '/'). */
  if (argv0 && argv0[0]) {
    last_sep_i = -1;
    for (i = 0; argv0[i]; i++) {
      if (argv0[i] == '/')
        last_sep_i = (int)i;
    }
    if (last_sep_i >= 0) {
      n = last_sep_i;
      /* mega: n >= sizeof(buf)-(3+rel_len) → empty. */
      if (n >= (int)sizeof(buf) - (int)(3 + rel_len))
        return link_abi_cstr_dup("");
      memcpy(buf, argv0, (size_t)n);
      buf[n] = '\0';
    } else {
      buf[0] = '.';
      buf[1] = '\0';
      n = 1;
    }
    /* mega guard n+3+rel_len < sizeof(buf); strcat "/../"+rel (prefix 4 bytes). */
    if ((size_t)n + 3 + rel_len < sizeof(buf)) {
      buf[n] = '/';
      buf[n + 1] = '.';
      buf[n + 2] = '.';
      buf[n + 3] = '/';
      memcpy(buf + n + 4, rel, rel_len + 1);
      rp = link_abi_realpath_cap(buf, resolved);
      if (rp)
        return link_abi_cstr_dup(rp);
      sm = asm_link_obj_skip_missing(buf);
      if (sm)
        return link_abi_cstr_dup(buf);
      return link_abi_cstr_dup("");
    }
  }
  return link_abi_cstr_dup("");
}

int32_t labi_path_pure_count(void) {
  return 58;
}


/* wave189: set/clear user_o_files pure orch (cold twin ≡ .x).
 * Cap residual reset/push live in mega always; pure owns argv scan.
 * PLATFORM: SHARED.
 */
void link_abi_user_extra_o_reset(void);
int link_abi_user_extra_o_push(const char *p);

void xlang_invoke_cc_set_user_o_files_from_argv(int argc, char **argv) {
    int i;
    link_abi_user_extra_o_reset();
    if (!argv)
        return;
    for (i = 1; i < argc; i++) {
        const char *a = argv[i];
        size_t len;
        if (!a || !a[0])
            continue;
        if (a[0] == '-') {
            if ((!strcmp(a, "-o") || !strcmp(a, "-L") || !strcmp(a, "-I") ||
                 !strcmp(a, "-target") || !strcmp(a, "-backend") ||
                 !strcmp(a, "-O") || !strcmp(a, "-opt")) && i + 1 < argc) {
                i++;
            }
            continue;
        }
        len = strlen(a);
        if (len >= 2 && a[len - 2] == '.' && a[len - 1] == 'o')
            (void)link_abi_user_extra_o_push(a);
    }
}

void xlang_invoke_cc_clear_user_o_files(void) {
    link_abi_user_extra_o_reset();
}


#else
int32_t labi_suffix_eq2(uint8_t *s, int32_t n, uint8_t a0, uint8_t a1);
int32_t labi_suffix_eq4(uint8_t *s, int32_t n, uint8_t a0, uint8_t a1, uint8_t a2, uint8_t a3);
int32_t link_abi_ld_argv_entry_is_obj(uint8_t *s);
int32_t xlang_output_is_elf_o(uint8_t *path);
int32_t xlang_output_want_exe(uint8_t *path);
int32_t xlang_path_has_sep(uint8_t *s);
uint8_t *xlang_path_last_sep(uint8_t *s);
int32_t xlang_asm_ld_lib_root_ptr_usable(uint8_t *p);
void xlang_asm_ld_lib_root_default(uint8_t *root_buf);
const char *xlang_asm_ld_try_under_lib_roots(const char *rel, const char **lib_roots, int n_lib_roots, void *bank);
int32_t link_abi_asm_ld_argv_has_obj(const char **argv, int la, const char *path);
void link_abi_asm_ld_argv_push_stable(void *bank, const char **argv, int *la, int max_la, const char *p);
int link_abi_asm_ld_push_obj(const char *primary, const char *link_argv0, const char *rel,
    const char **lib_roots, int n_lib_roots, void *bank, const char **argv, int *la, int max_la,
    int *flag_out);
void link_abi_asm_ld_push_glue_after_std(int have_std, int (*ensure_fn)(const char *argv0),
    const char *glue_primary, const char *link_argv0, const char *glue_rel,
    const char **lib_roots, int n_lib_roots, void *bank, const char **argv, int *la, int max_la);
void link_abi_asm_ld_push_minimal_runtime_objs(const char *link_argv0, const char **lib_roots,
    int n_lib_roots, void *bank, const char **argv, int *la, int max_la);
void xlang_asm_ld_append_user_extra_o_files(const char **argv, int *la, int max_la);
/* wave189 */
void xlang_invoke_cc_set_user_o_files_from_argv(int argc, char **argv);
void xlang_invoke_cc_clear_user_o_files(void);

int xlang_runtime_compiler_o_path_copy(const char *argv0, const char *leaf, char *out, size_t out_sz);
const char *xlang_repo_root_from_argv0(const char *argv0);
const char *xlang_runtime_panic_o_path(const char *argv0);
const char *xlang_crt0_user_o_path(const char *argv0);
const char *xlang_freestanding_io_o_path(const char *argv0);
const char *xlang_std_async_scheduler_o_path(const char *argv0);
const char *scheduler_o_for_task_link(const char *task_o, const char *explicit_scheduler);
const char *xlang_bootstrap_nostdlib_stubs_o_path(const char *argv0);
const char *xlang_runtime_asm_io_stubs_o_path(const char *argv0);
const char *xlang_runtime_process_argv_o_path(const char *argv0);
const char *xlang_runtime_process_os_glue_o_path(const char *argv0);
const char *xlang_runtime_test_fn_invoke_o_path(const char *argv0);
const char *xlang_runtime_random_fill_o_path(const char *argv0);
const char *xlang_runtime_compress_zlib_glue_o_path(const char *argv0);
const char *xlang_runtime_heap_user_o_path(const char *argv0);
const char *xlang_runtime_time_os_o_path(const char *argv0);
const char *xlang_runtime_queue_contention_o_path(const char *argv0);
const char *xlang_runtime_dynlib_os_o_path(const char *argv0);
const char *xlang_runtime_env_os_o_path(const char *argv0);
const char *xlang_runtime_link_abi_user_env_o_path(const char *argv0);
const char *xlang_runtime_backtrace_platform_o_path(const char *argv0);
const char *xlang_runtime_log_os_o_path(const char *argv0);
const char *xlang_runtime_math_libm_o_path(const char *argv0);
const char *xlang_runtime_atomic_glue_o_path(const char *argv0);
const char *xlang_runtime_channel_glue_o_path(const char *argv0);
const char *xlang_runtime_net_udp_batch_o_path(const char *argv0);
const char *xlang_runtime_net_workers_o_path(const char *argv0);
const char *xlang_runtime_sync_os_o_path(const char *argv0);
const char *xlang_runtime_sync_lock_diag_tls_o_path(const char *argv0);
const char *xlang_runtime_thread_glue_o_path(const char *argv0);
const char *xlang_runtime_scheduler_glue_o_path(const char *argv0);
const char *xlang_runtime_http_glue_o_path(const char *argv0);
const char *xlang_runtime_tls_mbedtls_bio_o_path(const char *argv0);
const char *xlang_runtime_kv_mmap_glue_o_path(const char *argv0);
const char *xlang_runtime_arrow_simd_glue_o_path(const char *argv0);
const char *xlang_runtime_sqlite_glue_o_path(const char *argv0);
const char *xlang_runtime_crypto_inc_glue_o_path(const char *argv0);
const char *xlang_runtime_ed25519_ref10_glue_o_path(const char *argv0);
const char *xlang_empty_cstr(void);
const char *xlang_std_io_o_path(const char *argv0);
const char *xlang_std_compress_o_path(const char *argv0);
const char *xlang_asm_ld_effective_link_argv0(const char *link_argv0, char *syn_buf, size_t syn_sz);
const char *xlang_rel_o_path_from_argv0(const char *argv0, const char *rel);
int32_t labi_path_pure_count(void);
#endif

int labi_path_pure_slice_marker(void) {
  return 1;
}
