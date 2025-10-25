#ifndef _GET_SYMBOL_FROM_CURRENT_PROCESS_H
#define _GET_SYMBOL_FROM_CURRENT_PROCESS_H

#include <stddef.h>

#ifdef _WIN32
  #include <windows.h>
#else
  #include <dlfcn.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

static inline void* get_symbol_from_current_process(const char* name) {
  if (name == NULL) {
    return NULL;
  }

#ifdef _WIN32
  HMODULE handle = GetModuleHandle(NULL);
  if (handle == NULL) {
    return NULL;
  }
  return (void*)GetProcAddress(handle, name);
#else
  void* handle = dlopen(NULL, RTLD_LAZY);
  if (handle == NULL) {
    return NULL;
  }

  void* sym = dlsym(handle, name);
  dlclose(handle);

  /* Clear any possible errors from dlsym */
  dlerror();

  return sym;
#endif
}

#ifdef __cplusplus
}
#endif

#endif /* _GET_SYMBOL_FROM_CURRENT_PROCESS_H */
