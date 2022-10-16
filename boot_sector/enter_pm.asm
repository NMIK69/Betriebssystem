enter_pm:
    cli
    lgdt[gdt_discriptor]
    mov eax, cr0
    or al, 0x01
    mov cr0, eax

    jmp CODE_SEG:bootloader32  ;far jump to set CS to CODE_SEG and IP to bootloader32 offset