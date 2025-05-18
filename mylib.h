// mylib.h
#ifndef MYLIB_H
#define MYLIB_H

// Para exportar o importar símbolos correctamente
#ifdef _WIN32
    #include <windows.h>

    typedef HMODULE din_lib;

    #define EXT_LIB ".dll"
    #define load_lib(name)                  LoadLibraryA(name EXT_LIB)
    #define get_error_lib(name)             (void)name
    #define load_simbol(handle, name)       GetProcAddress(handle, name)
    #define close_lib(handle)               FreeLibrary(handle);

    #ifdef BUILDING_MYLIB
        #define DLL_EXPORT __declspec(dllexport)
    #else
        #define DLL_EXPORT __declspec(dllimport)
    #endif
#elif defined(__linux__)
    #include <dlfcn.h>

    #define EXT_LIB ".so"

    typedef void * din_lib;

    #define load_lib(name)                  dlopen(name EXT_LIB, RTLD_LAZY)
    #define get_error_lib(name)             name = dlerror()
    #define load_simbol(handle, name)       dlsym(handle, name)
    #define close_lib(handle)               dlclose(handle);

    #define DLL_EXPORT __attribute__((visibility("default")))
#else
    #define DLL_EXPORT
#endif

// void *handle = dlopen("./mylib.so", RTLD_LAZY);
// HMODULE hDll = LoadLibraryA("mylib.dll");


DLL_EXPORT void hello_from_dll();

#endif // MYLIB_H