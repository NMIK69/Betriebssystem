#ifndef IO_PORTS_H
#define IO_PORTS_H


#include "../utils/typedefs.h"

void out_byte(uint16_t port_addr, uint8_t data);
void out_word(uint16_t port_addr, uint8_t data);
void out_dword(uint16_t port_addr, uint8_t data);

uint8_t in_byte(uint16_t port_addr);
uint16_t in_word(uint16_t port_addr);
uint32_t in_dword(uint16_t port_addr);


#endif