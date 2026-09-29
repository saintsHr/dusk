NAME := dusk
ARCHS := $(patsubst arch/%/Makefile,%,$(wildcard arch/*/Makefile))

ifndef ARCH
$(error ARCH not specified. Usage: make ARCH=<architecture> [rules]. Available: $(ARCHS))
endif

ifeq ($(filter $(ARCH),$(ARCHS)),)
$(error Invalid architecture '$(ARCH)'. Available: $(ARCHS))
endif

BUILD := build/$(ARCH)
ISODIR := $(BUILD)/iso

include arch/$(ARCH)/Makefile

CC := $(ARCH_CC)
AS := $(ARCH_AS)

INCLUDE := \
	-Iinclude

FLAGS_C := \
	$(ARCH_FLAGS_C) -ffreestanding -fno-pie \
    -fno-pic -fno-stack-protector -fno-builtin \
    -Wall -Wextra -O2 -MMD -MP $(INCLUDE) \
    -std=gnu17
FLAGS_LD := \
	$(ARCH_FLAGS_LD) -T $(ARCH_SCRIPT_LD) \
	-nostdlib -ffreestanding

SRC_C := \
	$(shell find kernel -name '*.c') \
	$(shell find drivers -name '*.c') \
	$(shell find lib -name '*.c') \
	$(ARCH_SRC_C)
SRC_ASM := \
	$(ARCH_SRC_ASM)

OBJ := $(SRC_C:%.c=$(BUILD)/%.o) $(SRC_ASM:%.asm=$(BUILD)/%.o)
DEP := $(OBJ:.o=.d)

KERNEL_ELF := $(BUILD)/$(NAME).elf
KERNEL_ISO := $(BUILD)/$(NAME).iso

.PHONY: all iso run clean bear

all: $(KERNEL_ELF)

$(KERNEL_ELF): $(OBJ) $(ARCH_SCRIPT_LD)
	@echo "  LD    $@"
	@$(CC) $(FLAGS_LD) -o $@ $(OBJ) -lgcc

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "  CC    $<"
	@$(CC) $(FLAGS_C) -c $< -o $@

$(BUILD)/%.o: %.asm
	@mkdir -p $(dir $@)
	@echo "  AS    $<"
	@$(AS) $(ARCH_FLAGS_AS) $< -o $@

iso: $(KERNEL_ISO)
$(KERNEL_ISO): $(KERNEL_ELF) boot/grub.cfg
	@echo "  ISO   $@"
	@mkdir -p $(ISODIR)/boot/grub
	@cp $(KERNEL_ELF) $(ISODIR)/boot/$(NAME).elf
	@cp boot/grub.cfg $(ISODIR)/boot/grub/grub.cfg
	@grub-mkrescue -o $@ $(ISODIR) 2>/dev/null

bear:
	@echo "  BEAR  compile_commands.json"
	@bear --output compile_commands.json -- \
		$(MAKE) --no-print-directory ARCH=$(ARCH) -B all

run: $(KERNEL_ISO)
	$(QEMU) -cdrom $(KERNEL_ISO)

clean:
	@echo "  CLEAN $(BUILD)"
	@rm -rf $(BUILD)

-include $(DEP)
