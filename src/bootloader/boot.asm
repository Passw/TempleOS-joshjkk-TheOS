global start
extern long_mode_start

section .text
bits 32
start:
    mov esp, stack_top

    call check_multiboot
    call check_cpuid
    call check_long_mode

    call setup_page_tables
    call enable_paging

    lgdt [gdt64.pointer] ; load global scriptor table
    jmp gdt64.code_segment:long_mode_start

    hlt

check_multiboot:
    cmp eax, 0x36d76289
    jne .no_multiboot
    ret
.no_multiboot:
    mov al, "M"                 ; M = multiboot
    jmp error

check_cpuid:
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 1 << 21
    push eax

    popfd
    pushfd

    pop eax
    push ecx
    popfd

    cmp eax, ecx
    je .no_cpuid
    ret
.no_cpuid:
    mov al, "C"                 ; C = cpu
    jmp error

check_long_mode:
    mov eax, 0x80000000         ; if does support long mode, a value which is higher gets
                                ; put back into eax
    cpuid
    cmp eax, 0x80000001
    jb .no_long_mode

    mov eax, 0x80000001         ; value wll be stored into edx, if lm is set, it is available
    cpuid
    test edx, 1 << 29           ; lm bit is at 29
    jz .no_long_mode
    ret
.no_long_mode:
    mov al, "L"                 ; L = long mode
    jmp error

setup_page_tables:
    mov eax, page_table_l3
    ; first 12 bits of every entry will be 0, cpu uses it to store flags instead
    or eax, 0b11                ; enable present and writable flags
    mov [page_table_l4], eax

    mov eax, page_table_l2
    ; first 12 bits of every entry will be 0, cpu uses it to store flags instead
    or eax, 0b11                ; enable present and writable flags
    mov [page_table_l3], eax

    ; identity mapping to enable l2 'huge page'
    mov ecx, 0                  ; counter starts at 0
.loop:

    ; map a 2MiB page
    mov eax, 0x200000           ; 2MiB
    mul ecx                     ; correct address for next page
    or eax, 0b10000011          ; present, writable, huge page
    ;         ^ 'huge page' flag
    mov [page_table_l2 + ecx * 8], eax

    inc ecx                     ; increment counter
    cmp ecx, 512                ; check if whole table is mapped
    jne .loop                   ; if not, continue

    ret

enable_paging:
    ; pass page table location to cpu
    mov eax, page_table_l4
    mov cr3, eax

    ; enable PAE (physical address extension) for 64-bit paging
    mov eax, cr4
    or eax, 1 << 5 ; PAE flag
    mov cr4, eax

    ; enable long mode
    mov ecx, 0xC0000080
    rdmsr ; read model specific register
    or eax, 1 << 8 ; long mode bit
    wrmsr ; write model specific register

    ; enable paging
    mov eax, cr0
    or eax, 1 << 31 ; paging bit
    mov cr0, eax

    ret

; print "ERR: X" where X is the error code
error:
    mov dword [0xb8000], 0x04f524f45
    mov dword [0xb8004], 0x4f3a4f52
    mov dword [0xb8008], 0x4f204f20
    mov byte  [0xb800a], al
    hlt

section .bss
align 4096                      ; align tables to 4KiB
page_table_l4:
    resb 4096                   ; 4KiB
page_table_l3:
    resb 4096                   ; 4KiB
page_table_l2:
    resb 4096                   ; 4KiB
stack_bottom:
    resb 4096 * 4               ; 16KiB
stack_top:

section .rodata                 ; read-only data
gdt64:
    dq 0                        ; zero entry
.code_segment: equ $ - gdt64
    dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53)                ; code segment
    ;        ^           ^          ^           ^
    ; executable   descriptor    present      64-bit
    ;   flag        type = 1      flag         flag
.pointer:
    dw $ - gdt64 - 1
    dq gdt64
