#ifndef SCREEN_H
#define SCREEN_H

#include "../utils/typedefs.h"

#define MAX_COLS 80
#define MAX_ROWS 25

#define VID_MEM_BASE 0xb8000
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4

#define PORT_SCREEN_CRTL 0x3d4
#define PORT_SCREEN_DATA 0x3d5


void screen_print_at(uint8_t* msg, int row, int col);
void screen_clear();

#endif