ASM = nasm
ASM_FLAGS = -f bin
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ggdb -std=c99
SRCDIR = src
TOOLSDIR = tools
BUILDDIR = build

.PHONY: all floppy_image kernel bootloader clean always tools_fat

all: floppy_image tools_fat

#
# Floppy image
#
floppy_image: $(BUILDDIR)/theos.img
$(BUILDDIR)/theos.img: bootloader kernel
	dd if=/dev/zero of=$(BUILDDIR)/theos.img bs=512 count=2880
	mkfs.fat -F 12 -n "THEOS" $(BUILDDIR)/theos.img
	dd if=$(BUILDDIR)/bootloader.bin of=$(BUILDDIR)/theos.img conv=notrunc
	mcopy -i $(BUILDDIR)/theos.img $(BUILDDIR)/kernel.bin "::kernel.bin"
	mcopy -i $(BUILDDIR)/theos.img test.txt "::test.txt"

#
# Bootloader
#
bootloader: $(BUILDDIR)/bootloader.bin
$(BUILDDIR)/bootloader.bin: always
	$(ASM) $(SRCDIR)/bootloader/boot.asm $(ASM_FLAGS) -o $(BUILDDIR)/bootloader.bin

#
# Kernel
#
kernel: $(BUILDDIR)/kernel.bin
$(BUILDDIR)/kernel.bin: always
	$(ASM) $(SRCDIR)/kernel/main.asm $(ASM_FLAGS) -o $(BUILDDIR)/kernel.bin

#
# Tools
#
tools_fat: $(BUILDDIR)/tools/fat
$(BUILDDIR)/tools/fat: always $(TOOLSDIR)/fat/fat.c $(TOOLSDIR)/fat/fat.h
	mkdir -p $(BUILDDIR)/tools
	$(CC) $(CFLAGS) -g -o $(BUILDDIR)/tools/fat $(TOOLSDIR)/fat/fat.c $(TOOLSDIR)/fat/fat.h


always:
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)/*
