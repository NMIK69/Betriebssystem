#include "../utils/typedefs.h"


/***************** send data to i/o port ********************/

void out_byte(uint16_t port_addr, uint8_t data) {
	asm volatile("outb %0, %1" : : "a"(data), "Nd"(port_addr));}

void out_word(uint16_t port_addr, uint8_t data) {
	asm volatile ("outw %w0, %1" : : "a" (data), "id" (port_addr) );
}
void out_dword(uint16_t port_addr, uint8_t data) {
	asm volatile ("outl %%eax, %%dx" :: "d" (port_addr), "a" (data));
}


/***************** read data from i/o port ********************/

uint8_t in_byte(uint16_t port_addr) {
    uint8_t recv;
	asm volatile("inb %1, %0" : "=a"(recv) : "Nd"(port_addr));
	return recv;
}
uint16_t in_word(uint16_t port_addr) {
   uint16_t recv;
   asm volatile ("inw %1, %0" : "=a" (recv) : "dN" (port_addr));
   return recv;
}
uint32_t in_dword(uint16_t port_addr) {
   uint32_t recv;
   asm volatile ("inl %1, %0" : "=a" (recv) : "dN" (port_addr));
   return recv;
}