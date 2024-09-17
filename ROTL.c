#include <stdio.h>
#include <stdint.h>
#include "algorithm.h"

//Rotate right function for a 32-bit word
uint32_t rotate_left(uint32_t value, uint32_t shift) {
  return (value << shift) ^ (value >> ((sizeof(value)* 8) - shift));
}
