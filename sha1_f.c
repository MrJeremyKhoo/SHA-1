#include <stdio.h>
#include <stdint.h>
#include "algorithm.h"

//Choose function: choose between y or z depending on the vlaue of x
uint32_t Choose(uint32_t x, uint32_t y, uint32_t z) {
  // Compute the expression (x n y) + (~x n z)
  return (x & y) | (~x & z);
}

//Parity function: determine pairity of bits between the inputs
uint32_t Parity(uint32_t x, uint32_t y, uint32_t z) {
  // Compute the expression x ^ y ^ z
  return x ^ y ^ z;
}

//Majority function: return majority aggregation of 1 bits between the 3 inputs.
uint32_t Majority(uint32_t x, uint32_t y, uint32_t z) {
  return (x & y) | (x & z) | (y & z);
}

//SHA-1 function
uint32_t sha1_f(uint8_t iteration_t, uint32_t x, uint32_t y, uint32_t z) {
  if(iteration_t >= 0 && iteration_t <= 19) { return Choose(x,y,z); } 
  else if (iteration_t >= 20 && iteration_t <= 39 ) { return Parity(x,y,z); } 
  else if (iteration_t >= 40 && iteration_t <= 59 ) { return Majority(x,y,z); } 
  else if (iteration_t >= 60 && iteration_t <= 79 ) { return Parity(x,y,z); } 
  else { perror("iteration_t out of range"); }
}
