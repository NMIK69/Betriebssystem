[org 0x7c00]
[bits 16]

KERNEL_LOCATION equ 0x7ef0


bootloader16:
    mov [BOOT_DISK], dl

    ;set up stack and segment registers
    cli
    mov ax, 0x00
    mov ds, ax
    mov es, ax

    mov ss, ax
    mov sp, 0x7c00
    sti

    ; clear the screen
    mov ah, 0x00
    mov al, 0x03
    int 0x10

    ; print msg that we are in real mode
    ;mov bx, rm_msg
    ;call print_string_rm
    ;call print_nl


    ; read disk and load kernel into memory
    mov bx, KERNEL_LOCATION ;where to load kernel to
    mov dh, 15              ;how many sectors after boot sector to load
    call disk_read

    ; switch to 32 bit protected mode
    jmp enter_pm


%include "boot_sector/print_string_rm.asm"
%include "boot_sector/print_hex.asm"
%include "boot_sector/disk_read.asm"
%include "boot_sector/gdt.asm"
%include "boot_sector/enter_pm.asm"


[bits 32]
bootloader32:

    ;set up stack and segment registers again with new data seg

    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov ebp, 0x90000
    mov esp, ebp

    ;enable A20 line for more memory access
    in al, 0x92
    or al, 0x02
    out 0x92, al

    mov ebx, kl_msg
    call print_string_pm

    jmp KERNEL_LOCATION

    jmp $



%include "boot_sector/print_string_pm.asm"


rm_msg: 
    db "Booted into 16-Bit Real-Mode",0
kl_msg:
    db "Kernel loaded successfully",0

times 510 - ($ - $$) db 0
dw 0xaa55     ; magick number