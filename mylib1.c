// mylib.c
#include "mylib1.h"
#include <stdio.h>

// Variable estática solo visible en este archivo
static int contador = 5;
DLL_EXPORT int  mi_variable_global1 = 0;

// Exportar funciones para acceder a la variable
DLL_EXPORT int get_contador1() {
    return contador;
}

DLL_EXPORT void incrementar_contador1() {
    contador++;
}

// Esta macro asegura la exportacion en Windows
DLL_EXPORT void hello_from_lib1() {
    printf("Hello from DLL!\n");
}