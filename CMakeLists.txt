cmake_minimum_required(VERSION 3.10)
project(MiProyecto C)

# Detectar sistema operativo y definir variables
if(WIN32)
    set(OS_NAME windows)
    set(EXTENSION_LIB dll)
    set(EXTENSION_EXEC exe)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2")
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_SUFFIX ".dll")
elseif(APPLE)
    set(OS_NAME macos)
    set(EXTENSION_LIB dylib)
    set(EXTENSION_EXEC elf)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2 -fPIC")
else()
    set(OS_NAME linux)
    set(EXTENSION_LIB so)
    set(EXTENSION_EXEC elf)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2 -fPIC")
endif()

# Buscar librerías en el directorio actual
set(SEARCH_DIR_LIB .)

# Compilar la biblioteca compartida (DLL/SO/DYLIB)
add_library(mylib SHARED mylib.c)

set_target_properties(mylib PROPERTIES PREFIX "")

# Definir macro para exportar símbolos si es necesario
target_compile_definitions(mylib PRIVATE BUILDING_MYLIB)

# Compilar el ejecutable
add_executable(main main.c)

# Enlazar el ejecutable con la librería si es necesario
target_link_libraries(main PRIVATE mylib)

# Opciones adicionales para Linux/macOS
if(UNIX AND NOT APPLE)
    target_link_libraries(main PRIVATE dl)
    set_target_properties(main PROPERTIES
            BUILD_RPATH "${CMAKE_CURRENT_SOURCE_DIR}/${SEARCH_DIR_LIB}"
    )
endif()

# Limpieza personalizada (opcional, CMake ya tiene 'clean')
add_custom_target(mi_clean
        COMMAND ${CMAKE_COMMAND} -E rm -f *.o *.${EXTENSION_EXEC} *.${EXTENSION_LIB}
)

# Mensajes informativos
message(STATUS "OS_NAME: ${OS_NAME}")
message(STATUS "EXTENSION_LIB: ${EXTENSION_LIB}")
message(STATUS "EXTENSION_EXEC: ${EXTENSION_EXEC}")
