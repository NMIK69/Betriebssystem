; load DH sectors to ES : BX from drive DL

disk_read:
    pusha
    push dx 

    cli
    mov ax, 0x0000
    mov es, ax
    sti

    mov ah, 0x02 ;read sector function
    mov al, dh ; Read dh sectors
    mov ch, 0x00 ; Select cylinder (0 indexed)
    mov dh, 0x00 ; Select head 1 (0 indexed)
    mov cl, 0x02 ; start sector 2 (1 indexed)
    mov dl, [BOOT_DISK] ; read from boot disk

    int 0x13 ;disk interrupt
    jc disk_error ;if overflow flag is set threre is an error

    pop dx
    cmp dh, al ; al now holds number of actual read sectros, cmp to dh
    jne disk_error ; display error message


    jmp disk_read_succ

disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string_rm
    call print_nl

    
    mov dh, ah
    call print_hex

    jmp $

disk_read_succ:
    mov bx, DISK_SUCC_MSG
    call print_string_rm

    popa
    ret

BOOT_DISK: 
    db 0x00
DISK_ERROR_MSG: 
    db "Disk read Error, Error Msg: " , 0
DISK_SUCC_MSG: 
    db "Disk read successfully", 0