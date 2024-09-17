#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "algorithm.h"

void sha1_pad(uint8_t *message, size_t length, uint8_t **padded_message, size_t * padded_length) {
  const size_t BLOCK_SIZE = 64; //SHA-1 block size in bytes (512 bits)
  const size_t LENGTH_SIZE = 8; //Length field size in bytes (64 bits)
 
  //Calculate the number of padding bytes needed
  size_t original_size = length;
  size_t padding_needed = BLOCK_SIZE - ((original_size + 1 + LENGTH_SIZE) % BLOCK_SIZE);
  if (padding_needed == BLOCK_SIZE) {
    padding_needed = 0;
  }
  
  // Allocate mem
  *padded_length = original_size + 1 + padding_needed + LENGTH_SIZE;
  *padded_message = (uint8_t *)malloc(*padded_length);
  if(*padded_message == NULL) {
    perror("Unable to allocate memory for padding");
    exit(EXIT_FAILURE);
  }

  //Copy the original message
  memcpy(*padded_message, message, original_size);

  //Append the '1' bit
  (*padded_message)[original_size] = 0x80;

  //Append the '0' bit
  memset(*padded_message + original_size + 1, 0, padding_needed);

  //Append the length of the original message in bits
  uint64_t bit_length = original_size * 8;
  for(size_t i =0; i < LENGTH_SIZE; ++i) {
    (*padded_message)[original_size + 1 + padding_needed + i] = (bit_length >> (56 - i * 8)) & 0xFF;
  }

}

int main() {
    // test
    uint8_t message[] = "abc";
    size_t length = sizeof(message) - 1; // Length of the message (excluding null terminator)

    // Pad the message
    uint8_t *padded_message = NULL;
    size_t padded_length = 0;
    sha1_pad(message, length, &padded_message, &padded_length);

    // Print the padded message in hex
    printf("Padded message (length: %zu bytes):\n", padded_length);
    for (size_t i = 0; i < padded_length; ++i) {
        printf("%02X ", padded_message[i]);
    }
    printf("\n");

    // Free allocated memory
    free(padded_message);

    return 0;
}
