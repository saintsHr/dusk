CROSS := i386-elf-

ARCH_CC := $(CROSS)gcc
ARCH_AS := nasm

ARCH_FLAGS_AS := \
	-f elf32
ARCH_FLAGS_C := \
    -m32 -march=i386 -mgeneral-regs-only \
    -mno-sse -mno-sse2 -mno-mmx -mno-avx
ARCH_FLAGS_LD := \
	-m32

ARCH_SCRIPT_LD := linker/i386.ld

ARCH_SRC_C := $(shell find arch/i386 -name '*.c')
ARCH_SRC_ASM := $(shell find arch/i386 -name '*.asm')

QEMU := qemu-system-i386
