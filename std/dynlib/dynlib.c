/**
 * std/dynlib/dynlib.c — 动态加载 .so/.dll（对标 Zig std.DynLib、Rust libloading）
 *
 * 【文件职责】open(path)、sym(lib, name)、close(lib)；POSIX dlopen/dlsym/dlclose，Windows LoadLibrary/GetProcAddress/FreeLibrary。
 *
 * 【所属模块/组件】标准库 std.dynlib；与 std/dynlib/mod.su 同属一模块。按需链接。
 */

#include <stdint.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
typedef HMODULE dynlib_handle_t;
#else
#include <dlfcn.h>
typedef void *dynlib_handle_t;
#endif

/** 打开动态库 path（NUL 结尾）；失败返回 0。返回不透明句柄。path 为 NULL 或空字符串时返回 0，避免 Linux 上 dlopen("") 返回主程序句柄导致测试/行为不一致。 */
void *dynlib_open_c(const uint8_t *path) {
  if (!path || !path[0]) return NULL;
#if defined(_WIN32) || defined(_WIN64)
  return (void *)LoadLibraryA((const char *)path);
#else
  return dlopen((const char *)path, RTLD_NOW);
#endif
}

/** 取符号 name（NUL 结尾）；失败返回 0。 */
void *dynlib_sym_c(void *lib, const uint8_t *name) {
  if (!lib || !name) return NULL;
#if defined(_WIN32) || defined(_WIN64)
  return (void *)GetProcAddress((HMODULE)lib, (const char *)name);
#else
  return dlsym(lib, (const char *)name);
#endif
}

/** 关闭动态库。 */
void dynlib_close_c(void *lib) {
  if (!lib) return;
#if defined(_WIN32) || defined(_WIN64)
  FreeLibrary((HMODULE)lib);
#else
  dlclose(lib);
#endif
}
