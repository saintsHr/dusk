AS = nasm
CC = i686-elf-gcc

QEMU = qemu-system-x86_64

SRC_C = $(shell find src -type f -name '*.c')
SRC_S = $(shell find src -type f -name '*.asm')

OBJ = \
	$(SRC_C:src/%.c=build/%.c.o) \
	$(SRC_S:src/%.asm=build/%.asm.o)

HD     = extras/hd.img
FORMAT = raw
IF     = ide

QEMUMEM = 512
QEMUCPU = qemu64

QEMUFLAGS = \
	-cdrom build/$(NAME).iso \
	-serial mon:stdio \
	-m $(QEMUMEM) \
	-cpu $(QEMUCPU) \

QEMUEXTRAFLAGS = \
	-drive file=$(HD),format=$(FORMAT),if=$(IF) \

ASFLAGS = \
	-f elf32

CFLAGS = \
	-Iinclude \
	-std=gnu99 \
	-ffreestanding \
	-O0 \
	-Wall \
	-Wextra \
	-m32 \
	-fno-stack-protector \
	-fno-pic \
	-fno-pie \
	-fno-builtin \
	-g

LDFLAGS = \
	-ffreestanding \
	-nostdlib \
	-nodefaultlibs \
	-lgcc \
	-mno-sse \
	-mno-mmx \
	-Wl,--build-id=none \
	-Wl,-n 

NAME = dusk

.PHONY: all iso test test-extra run run-extra clean cloc reset bear

all: build/$(NAME).bin
iso: build/$(NAME).iso

test: 
	$(MAKE) all
	$(MAKE) iso
	$(MAKE) run
	clear

test-extra: 
	$(MAKE) all
	$(MAKE) iso
	$(MAKE) run-extra
	clear

clean:
	rm -rf bin
	rm -rf build
	rm -rf isodir

build/$(NAME).iso: build/$(NAME).bin
	mkdir -p isodir/boot/grub
	cp build/$(NAME).bin isodir/boot/$(NAME).bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o build/$(NAME).iso isodir

run-extra: build/$(NAME).iso
	$(QEMU) $(QEMUFLAGS) $(QEMUEXTRAFLAGS)

run: build/$(NAME).iso
	$(QEMU) $(QEMUFLAGS)

cloc:
	cloc ./src ./include

bear:
	$(MAKE) clean
	mkdir -p build
	touch build/compile_commands.json
	bear --output build/compile_commands.json -- make

reset:
	git fetch origin
	git reset --hard origin/main
	git clean -fd

build/%.asm.o: src/%.asm
	mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

build/%.c.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

build/$(NAME).bin: $(OBJ)
	mkdir -p build
	$(CC) -T linker.ld -o $@ $(LDFLAGS) $^
