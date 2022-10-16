print_hex:
    pusha

    mov bx, hex_out + 5 ; hexout offset where the LSB goes

    mov cl, 0
    .loop:


        cmp cl, 4
        je .end
        inc cl      ; inc counter and repeat if less then 4


        mov ax, dx
        and ax, 0x0f
        shr dx, 4    ;get last 4 bit
 
        cmp al, 0x09  ;check if its char or num
        jle is_num
        jg is_char


    .end:
        mov bx, hex_out
        call print_string_rm
        popa
        ret


is_num:
    
    add al, 0x30
    mov [bx], al
    dec bx

    jmp print_hex.loop

is_char:
    
    add al, 0x37
    mov [bx], al
    dec bx
    
    jmp print_hex.loop

hex_out: db "0x0000",0