#include <stdio.h>
#include <stdint.h>

#define LENGTH_SIZE 8 // SHA-1 uses 8 bytes to store the message length

void print_padded_message(uint8_t* padded_message, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf("%02x ", padded_message[i]);
    }
    printf("\n");
}

int main() {
    // Example: original message size in bytes
    size_t original_size = 55; // Let's say the original message is 55 bytes
    uint64_t bit_length = original_size * 8; // Convert size to bits
    
    // Assume enough space for the padded message
    size_t padded_size = original_size + 1 + LENGTH_SIZE; // Original + 0x80 + Length
    uint8_t padded_message[64] = {0}; // Initialize padded message (just an example buffer)

    // Padding example (0x80 after the message, plus padding bytes)
    padded_message[original_size] = 0x80; // Add the '1' bit (0x80)

    printf("Initial padded message (after adding 0x80):\n");
    print_padded_message(padded_message, padded_size - LENGTH_SIZE); // Print the current state

    // Now, append the length of the message in bits (64-bit big-endian)
    for (size_t i = 0; i < LENGTH_SIZE; ++i) {
        padded_message[original_size + 1 + i] = (bit_length >> (56 - i * 8)) & 0xFF;

        // Display what happens at each step
        printf("After iteration %zu (bit_length >> %zu) & 0xFF:\n", i, (56 - i * 8));
        print_padded_message(padded_message, padded_size);
    }

    return 0;
}

