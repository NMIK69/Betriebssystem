#include "../utils/typedefs.h"
#include "screen.h"
#include "io_ports.h"
#include "../kernel/mem_utils.h"


void _print_char(uint8_t c);
uint16_t _get_vga_offset(int row, int col);
void _set_cursor_offset();
void _set_vga_offset(uint16_t n_offset);
uint16_t _get_cursor_offset();
int _vga_offset_to_row();
void _scroll_handler();
int _vga_offset_to_col();



uint16_t vga_offset = 0;


void screen_print_at(uint8_t* msg, int row, int col) {

    vga_offset = _get_vga_offset(row, col);
    if(row == -1 && col == -1) {
        vga_offset = _get_cursor_offset() * 2;
    }

    uint32_t i = 0;

    while(msg[i] != 0) {

        _print_char(msg[i]);
        i += 1;

        _set_vga_offset(vga_offset + 2);
        _scroll_handler();
        _set_cursor_offset();
    }

}
void screen_clear() {
    vga_offset = 0;

    for(uint16_t i = 0; i < MAX_ROWS; i++) {
        for(uint16_t j = 0; j < MAX_COLS; j++) {
            _print_char(' ');
            vga_offset += 2;
        }

    }
    
    vga_offset = 0;
    _set_cursor_offset();

}

void _print_char(uint8_t c) {

    uint8_t* vid_mem = (uint8_t*)VID_MEM_BASE;


    // check for arrow key
    if(c == ARROW_LEFT) {

        if(vga_offset == 0) {
            vga_offset -= 2;
            return;
        }

        vga_offset -= 4;
        return;
    }
    else if(c == ARROW_RIGHT) {
        return;
    }

    // first check if char is a new line 
    else if(c == '\n') {
        // if so then set vga_offset accordingly
        int curr_row = _vga_offset_to_row();
        vga_offset = _get_vga_offset(curr_row + 1, 0) - 2;

        return;
    }

    //check if char is a backspace
    else if(c == '\b') {

        if(vga_offset == 0) {
            vga_offset -= 2;
            return;
        }

        int curr_row = _vga_offset_to_row();
        int curr_col = _vga_offset_to_col();
        vga_offset -= 2;
        *(vid_mem + vga_offset) = ' '; 
        *(vid_mem + vga_offset + 1) = WHITE_ON_BLACK;

        vga_offset -= 2;
        return;
    }


    *(vid_mem + vga_offset) = c; // char to print
    *(vid_mem + vga_offset + 1) = WHITE_ON_BLACK; // color scheme
}

uint16_t _get_vga_offset(int row, int col) {
    return ((row * MAX_COLS) + col) * 2;
}

void _set_cursor_offset() {

    uint16_t offset = vga_offset / 2; // div by 2 so we get the logical offset

    out_byte(PORT_SCREEN_CRTL, 14); // send high byte
    out_byte(PORT_SCREEN_DATA, (uint8_t)(offset >> 8));

    out_byte(PORT_SCREEN_CRTL, 15); // send low byte
    out_byte(PORT_SCREEN_DATA, (uint8_t)(offset & 0xff));

}

void _set_vga_offset(uint16_t n_offset) {
    vga_offset = n_offset;
}

int _vga_offset_to_row() {
    return (int)(vga_offset / 160);
}

int _vga_offset_to_col() {
    int temp = (int)vga_offset;
    int col = temp % 50;
    return col;
}

uint16_t _get_cursor_offset() {
    /**** this function returns the logical offset from the topleft cornor of the screen ****/ 
    /*** the vga_offset = cursor offset * 2 ***/

    uint16_t cursor_offset;

    out_byte(PORT_SCREEN_CRTL, 14); //high byte first
    cursor_offset += in_byte(PORT_SCREEN_DATA);
    cursor_offset = cursor_offset << 8;

    out_byte(PORT_SCREEN_CRTL, 15); //low byte
    cursor_offset += in_byte(PORT_SCREEN_DATA);

    
    return cursor_offset;
}

void _scroll_handler() {


    // check if scrolling is nesseary
    if(vga_offset <= (MAX_COLS * MAX_ROWS * 2)) {
        return;
    }

    // else we need to scroll down
    /*this means:
        -shifting all rows up by one
        -clear last row
        -set cursor to start of last row
    */

    // shift up rows
    uint8_t* temp_vid_mem = (uint8_t*)VID_MEM_BASE;
    for(uint32_t i = 0; i < MAX_ROWS; i++) {
        mem_copy(temp_vid_mem, temp_vid_mem + (MAX_COLS*2), (MAX_COLS*2));
        temp_vid_mem += (MAX_COLS*2);
    }   

    // clear last row
    uint16_t temp_vga_offset = _get_vga_offset(MAX_ROWS, 0);
    for(uint32_t i = 0; i < MAX_COLS; i++) {
        _print_char(' ');
        temp_vga_offset += 2;
    }

    // set cursor to last row
    vga_offset = _get_vga_offset(MAX_ROWS-1, 0);
    _set_cursor_offset();
}