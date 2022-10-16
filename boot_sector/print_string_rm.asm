print_string_rm:

    pusha
    mov ah, 0x0e ;tty mode

    .loop:

        mov al, [bx] ;check if char is null
        cmp al, 0x00 

        je .end ; if null then string is terminated

        ;else print char to screen
        int 0x10

        ;inc bx by one to get next bye (char)
        inc bx
        jmp .loop
    
    .end:
        popa
        ret

print_nl:

    pusha

    mov ah, 0x0e ;tty mode
    mov al, 0x0a ;nl 
    int 0x10

    mov al, 0x0d ;cr 
    int 0x10

    popa
    ret
