CC = clang
LD = clang
AS = nasm

ARCH=amd64

CFLAGS = -Wall -pipe -Iinclude/ -std=gnu11 -O2 -nostdlib -ffreestanding
LFLAGS = $(CFLAGS) -Llib/
ASFLAGS = -f elf64

MLIBC_SOURCES = $(wildcard src/*.c)
MLIBC_SOURCES += $(wildcard arch/${ARCH}/*.asm)

TMP_OBJECTS = $(MLIBC_SOURCES:.c=.o)
MLIBC_OBJECTS = $(TMP_OBJECTS:.asm=.o)

LIB_DIR = lib

mlibc: $(MLIBC_OBJECTS)
	ar rcs $(LIB_DIR)/libminimalc.a $(MLIBC_OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	find . -type f \( -name "*.o" -o -name "*.a" \) -exec rm {} \;

.PHONY: clean
