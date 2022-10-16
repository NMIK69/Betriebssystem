#include "../utils/typedefs.h"
#include "mem_utils.h"



void mem_copy(uint8_t* dest, uint8_t* src, uint32_t n_bytes) {

    uint32_t i = 0;

    while(i < n_bytes) {

        *(dest + i) = *(src + i);

        i += 1;
    }
}