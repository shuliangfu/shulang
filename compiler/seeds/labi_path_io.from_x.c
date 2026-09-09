/* seeds/labi_path_io.from_x.c — G-02f-270/L P2 link_abi L3 path IO → R2 full
 * Logic source: src/runtime/labi_path_io.x
 * Hybrid: XLANG_LABI_PATH_IO_FROM_X + ld -r into runtime_link_abi.o
 *
 * R2 full（2026-07-14 + wave209 + wave218 + wave221）：公共业务符号由 full .x 提供：
 *   xlang_path_is_nonempty_regular_file + asm_link_obj_skip_missing
 *   + xlang_runtime_o_realpath_if_exists + link_abi_path_readable
 *   + link_abi_realpath_cap + link_abi_path_executable + labi_path_io_count
 * Cap residual（mega rest 常驻）：
 *   xlang_path_is_nonempty_regular_file_impl（struct stat / S_ISREG）
 *   xlang_runtime_o_realpath_if_exists_impl（libc realpath + skip）
 *   link_abi_path_readable_impl（host access R_OK; wave209）
 *   link_abi_realpath_cap_impl（POSIX realpath / Windows null; wave218）
 *   link_abi_path_executable_impl（host access X_OK; wave221）
 * FROM_X 下本文件仅前向声明 + slice marker（产品 rest 业务 H=0）。
 * 冷启动/无 PREFER 时仍编译完整 C thin 体（可与 mega _impl 并存）。
 *
 */
#include <stddef.h>

/* OS bodies provided by runtime_link_abi.from_x.c rest (always). */
int xlang_path_is_nonempty_regular_file_impl(const char *path);
const char *xlang_runtime_o_realpath_if_exists_impl(const char *path, char *resolved);
int link_abi_path_readable_impl(const char *path);
const char *link_abi_realpath_cap_impl(const char *path, char *out);
int link_abi_path_executable_impl(const char *path);

#ifndef XLANG_LABI_PATH_IO_FROM_X

int xlang_path_is_nonempty_regular_file(const char *path) {
  if (path == NULL)
    return 0;
  if (path[0] == 0)
    return 0;
  return xlang_path_is_nonempty_regular_file_impl(path);
}

const char *asm_link_obj_skip_missing(const char *path) {
  if (path == NULL)
    return NULL;
  if (path[0] == 0)
    return NULL;
  if (xlang_path_is_nonempty_regular_file(path) == 0)
    return NULL;
  return path;
}

const char *xlang_runtime_o_realpath_if_exists(const char *path, char *resolved) {
  if (path == NULL)
    return NULL;
  if (path[0] == 0)
    return NULL;
  if (resolved == NULL)
    return NULL;
  return xlang_runtime_o_realpath_if_exists_impl(path, resolved);
}

/* wave209: path_readable pure orch cold twin (null/empty gates + Cap residual access). */
int link_abi_path_readable(const char *path) {
  if (path == NULL)
    return 0;
  if (path[0] == 0)
    return 0;
  return link_abi_path_readable_impl(path);
}

/* wave218: realpath_cap pure orch cold twin (null/empty/out gates + Cap residual realpath). */
const char *link_abi_realpath_cap(const char *path, char *out) {
  if (path == NULL)
    return NULL;
  if (path[0] == 0)
    return NULL;
  if (out == NULL)
    return NULL;
  return link_abi_realpath_cap_impl(path, out);
}

/* wave221: path_executable pure orch cold twin (null/empty gates + Cap residual X_OK). */
int link_abi_path_executable(const char *path) {
  if (path == NULL)
    return 0;
  if (path[0] == 0)
    return 0;
  return link_abi_path_executable_impl(path);
}

/* Pure audit: number of L3 thin path-IO gates (wave221: + path_executable). */
int labi_path_io_count(void) {
  return 6;
}

#else
int xlang_path_is_nonempty_regular_file(const char *path);
const char *asm_link_obj_skip_missing(const char *path);
const char *xlang_runtime_o_realpath_if_exists(const char *path, char *resolved);
int link_abi_path_readable(const char *path);
const char *link_abi_realpath_cap(const char *path, char *out);
int link_abi_path_executable(const char *path);
int labi_path_io_count(void);
#endif

int labi_path_io_slice_marker(void) {
  return 1;
}
