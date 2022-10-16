#include "typedefs.h"
#include "conversions.h"


void uint32_to_string(uint32_t num, char* s, uint8_t size) {

    uint32_t i = 0;
    uint32_t last_digit;

    while(i < (size - 1)) {

        last_digit = num % 10;
        
        s[i] = '0'+last_digit;

        num = num / 10;

        i += 1;

        if(num == 0) break;
    }

    s[i] = 0;

    string_reverse(s);
}
void string_reverse(char* s) {

    uint32_t start = 0;
    uint32_t end = srting_len(s) - 1;

    char temp;

    while(start < end) {
        temp = s[start];
        s[start] = s[end];
        s[end] = temp;

        start += 1;
        end -= 1;
    }
}

uint32_t srting_len(char* s) {

    uint32_t i = 0;
    while(s[i] != 0) {
        i += 1;
    }

    return i;
}