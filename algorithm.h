//algorithm.h
#ifndef ALGO_H
#define ALGO_H

uint32_t rotate_left(uint32_t value, uint32_t shift);
uint32_t rotate_right(uint32_t value, uint32_t shift);
void sha1_pad(uint8_t *message, size_t length, uint8_t **padded_message, size_t * padded_length);
uint32_t sha1_f(uint8_t iteration_t, uint32_t x, uint32_t y, uint32_t z);

#endif
