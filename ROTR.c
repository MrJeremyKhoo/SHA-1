#include <stdio.h>
#include <stdint.h>
#include "algorithm.h"

//Rotate right function for a 32-bit word
uint32_t rotate_right(uint32_t value, uint32_t shift) {
  return (value >> shift) ^ (value << ((sizeof(value)* 8) - shift));
}

int main() {
    uint32_t value = 0b10101010; // Example value
    uint32_t shift = 1;          // Number of positions to rotate

    uint32_t rotated = rotate_right(value, shift);

    printf("Original value: 0b%08X\n", value);
    printf("Rotated value: 0b%08X\n", rotated);

    return 0;
}
