#include "din_lib_c.h"

#include <stdlib.h>

static void (*constructor) (void) = NULL;
static void (*destructor) (void) = NULL;

void register_init(void);

#ifdef _WIN32
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch(fdwReason) {
        case DLL_PROCESS_ATTACH: register_init(); if (constructor) constructor(); break;
        case DLL_PROCESS_DETACH: if (destructor) destructor(); break;
    }
    return TRUE;
}

#elif defined(__linux__)
__attribute__((constructor)) DLL_EXPORT void os_register__(void) { register_init(); if (constructor != NULL) constructor(); }
__attribute__((destructor)) DLL_EXPORT void dtor__(void) { if (destructor != NULL) destructor(); }
#else
    #define MODULE_INIT_DESTRUCTOR(constructor, destructor)

    // estas funciones no tienen utilidad en windows, ya que no es necesario registrar
    // las funciones de inicializacion y destruccion a traves de funciones especiales como estas
    __attribute__((used)) DLL_EXPORT void os_register__(void) { }
    __attribute__((used)) DLL_EXPORT void dtor__(void) {  }
    void *force_link[] = { (void*)os_register__, (void*)dtor__ };

#endif

