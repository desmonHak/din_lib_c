#include "mylib.h"
#include <stdio.h>

typedef void (*hello_func_t)(void);
typedef int (*get_contador_t)(void);
typedef void (*incrementar_contador_t)(void);

DLL_EXPORT extern int mi_variable_global;

int main() {
    char *error = NULL;

    din_lib handle = load_lib("./mylib");
    if (!handle) {
        get_error_lib(error);
        fprintf(stderr, "No se pudo cargar la SO: %s\n", error);
        return 1;
    }
    din_lib mylib1 = load_lib("./mylib1");
    if (!handle) {
        get_error_lib(error);
        fprintf(stderr, "No se pudo cargar la SO: %s\n", error);
        return 1;
    }

    get_error_lib(error); // Limpiar errores previos
    printf("./mylib" EXT_LIB " se cargo correctamente.\n");

    hello_func_t hello_from_lib = (hello_func_t)load_simbol(handle, "hello_from_lib");
    get_error_lib(error);
    if (error != NULL) {
        fprintf(stderr, "No se pudo obtener la funcion hello_from_lib: %s\n", error);
        close_lib(handle);
        return 1;
    }

    get_contador_t get_contador = (get_contador_t)load_simbol(handle, "get_contador");
    get_error_lib(error);
    if (error != NULL) {
        fprintf(stderr, "No se pudo obtener la funcion get_contador: %s\n", error);
        close_lib(handle);
        return 1;
    }

    incrementar_contador_t incrementar_contador = (incrementar_contador_t)load_simbol(handle, "incrementar_contador");
    get_error_lib(error);
    if (error != NULL) {
        fprintf(stderr, "No se pudo obtener la funcion incrementar_contador: %s\n", error);
        close_lib(handle);
        return 1;
    }

    // Usar las funciones
    hello_from_lib();

    printf("Contador inicial: %d\n", get_contador());

    incrementar_contador();
    incrementar_contador();

    printf("Contador despues de incrementar dos veces: %d\n", get_contador());

    // Si tu biblioteca exporta `mi_variable_global`, puedes accederla así
    int *ptr_var_global = (int *)load_simbol(handle, "mi_variable_global");
    get_error_lib(error);
    if (ptr_var_global) {
        printf("Valor de mi_variable_global desde la SO: %d\n", *ptr_var_global);
    } else {
        printf("No se pudo obtener mi_variable_global: %s\n", error);
    }
    close_lib(mylib1);
    close_lib(handle);
    return 0;
}
