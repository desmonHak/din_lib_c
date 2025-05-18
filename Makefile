ifeq ($(OS),Windows_NT)
    OS_NAME := windows
else
    UNAME_S := $(shell uname -s)

    ifeq ($(UNAME_S),Linux)
        OS_NAME := linux
    endif

    ifeq ($(UNAME_S),Darwin)
        OS_NAME := macos
    endif
endif


# lugar donde buscar el .so
SEARCH_DIR_LIB = .

ifeq ($(OS_NAME),windows)
	EXTENSION_LIB	= dll
	EXTENSION_EXEC	= exe
	CFLAGS			= -Wall -O2
	RM				= del /Q

	CFLAGS_EXEC		= $(CFLAGS)
else
	EXTENSION_LIB	= so
	EXTENSION_EXEC	= elf
	CFLAGS			= -Wall -O2 -fPIC
	RM				= rm -rf

	CFLAGS_EXEC		= $(CFLAGS) -ldl -Wl,-rpath=$(SEARCH_DIR_LIB)
endif

CC = gcc


# Para compilar DLL: define BUILDING_MYLIB para exportar símbolos
DLL_NAME = mylib.$(EXTENSION_LIB)
DLL_OBJS = mylib.o

# Ejecutable que usa la DLL cargándola en runtime
EXE_NAME = main.$(EXTENSION_EXEC)
EXE_OBJS = main.o



.PHONY: all clean

all: $(DLL_NAME) $(EXE_NAME)

# Crear DLL
$(DLL_NAME): $(DLL_OBJS)
	$(CC) -shared -o $@ $^

mylib.o: mylib.c mylib.h
	$(CC) $(CFLAGS) -DBUILDING_MYLIB -c mylib.c

# Ejecutable ejemplo
$(EXE_NAME): $(EXE_OBJS)
	$(CC) $(CFLAGS_EXEC)  -o $@ $^

main.o: main.c mylib.h
	$(CC) $(CFLAGS) -c main.c

clean:
	$(RM) *.o *.$(EXTENSION_EXEC) *.$(EXTENSION_LIB)
