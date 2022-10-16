#include "../utils/typedefs.h"
#include "../drivers/io_ports.h"
#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../drivers/keyboard.h"


extern void main() {
    screen_clear();
    
    isr_install();
    asm volatile("sti");

    init_keyboard();


    screen_print_at("MFOS, a shitty 32bit-OS\nThe only thing you can do is type to yourself\n", -1, -1);

    return;
}