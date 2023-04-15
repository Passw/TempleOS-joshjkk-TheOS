OUT = TheOS

KERNEL_SOURCES := src/kernel/main.c
KERNEL_OBJECTS := $(patsubst src/kernel/main.c, build/kernel/main.o, $(KERNEL_SOURCES))

x86_64_C_SOURCES := $(shell find src/kernel/lib -name *.c)
x86_64_C_OBJECTS := $(patsubst src/kernel/lib/%.c, build/lib/%.o, $(x86_64_C_SOURCES))

x86_64_ASM_SOURCES := $(shell find src -name *.asm)
x86_64_ASM_OBJECTS := $(patsubst src/%.asm, build/%.o, $(x86_64_ASM_SOURCES))

x86_64_OBJECTS := $(x86_64_C_OBJECTS) $(x86_64_ASM_OBJECTS)

CFLAGS := -Wall -Wextra -pedantic -ggdb -std=c99 -ffreestanding
INCLUDES := -I src/kernel/include -I src/compiler/include

$(KERNEL_OBJECTS): build/kernel/%.o : src/kernel/%.c
	mkdir -p $(dir $@) && \
	gcc $(INCLUDES) -c $(CFLAGS) $(patsubst build/kernel/%.o, src/kernel/%.c, $@) -o $@

$(x86_64_C_OBJECTS): build/%.o : src/kernel/%.c
	mkdir -p $(dir $@) && \
	gcc $(INCLUDES) -c $(CFLAGS) $(patsubst build/%.o, src/kernel/%.c, $@) -o $@

$(x86_64_ASM_OBJECTS): build/%.o : src/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/%.o, src/%.asm, $@) -o $@

.PHONY: debian
debian: $(KERNEL_OBJECTS) $(x86_64_OBJECTS)
	mkdir -p dist && \
	ld -n -o dist/kernel.bin -T targets/linker.ld $(KERNEL_OBJECTS) $(x86_64_OBJECTS) && \
	cp dist/kernel.bin targets/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/$(OUT).iso targets/iso
