LIBS = mylib mylib1
EXE_NAME = main

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

ifeq ($(OS_NAME),windows)
    EXTENSION_LIB  = dll
    EXTENSION_EXEC = exe
    CFLAGS         = -Wall -O2
    RM             = del /Q
    CFLAGS_EXEC    = $(CFLAGS)
    DLL_EXPORT_MACRO = -DBUILDING_DLL
else
    EXTENSION_LIB  = so
    EXTENSION_EXEC = elf
    CFLAGS         = -Wall -O2 -fPIC
    RM             = rm -rf
    CFLAGS_EXEC    = $(CFLAGS) -ldl -Wl,-rpath=.
    DLL_EXPORT_MACRO = -DBUILDING_DLL
endif

CC = gcc

# Genera nombres de archivos automáticamente
DLL_NAMES = $(foreach lib,$(LIBS),$(lib).$(EXTENSION_LIB))
DLL_OBJS  = $(foreach lib,$(LIBS),$(lib).o)
EXE_FILE  = $(EXE_NAME).$(EXTENSION_EXEC)
EXE_OBJS  = $(EXE_NAME).o

.PHONY: all clean

all: $(DLL_NAMES) $(EXE_FILE)

# Regla general para cada librería dinámica
%.dll: %.o
	$(CC) -shared -o $@ $^

%.so: %.o
	$(CC) -shared -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -DBUILDING_DIN_LYB -c $<

# Ejecutable
$(EXE_FILE): $(EXE_OBJS)
	$(CC) $(CFLAGS_EXEC) -o $@ $^

$(EXE_NAME).o: $(EXE_NAME).c $(addsuffix .h,$(LIBS))
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o *.$(EXTENSION_EXEC) *.$(EXTENSION_LIB)
