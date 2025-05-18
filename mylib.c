// mylib.c
#include "mylib.h"
#include <stdio.h>

#include "init.c"

static inline void os_constructor(void) { 
    puts("hola desde el constructor de mylib"); 
}
static inline void os_destructor(void) { 
    puts("hola desde el destructor  de mylib"); 
}

void register_os_init(void) {
    constructor = os_constructor;
    destructor = os_destructor;
}

// Variable estática solo visible en este archivo
static int contador = 5;
DLL_EXPORT int  mi_variable_global = 0;

// Exportar funciones para acceder a la variable
DLL_EXPORT int get_contador() {
    return contador;
}

DLL_EXPORT void incrementar_contador() {
    contador++;
}

// Esta macro asegura la exportacion en Windows
DLL_EXPORT void hello_from_lib() {
    printf("Hello from DLL!\n");
}