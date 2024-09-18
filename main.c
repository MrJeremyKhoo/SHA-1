#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "algorithm.h"

#define SHA1_BLOCK_SIZE 64
#define SHA1_DIGEST_SIZE 20

typedef struct {
  uint32_t h[5];
  uint32_t count[2];
  uint8_t buffer[SHA1_BLOCK_SIZE];
} SHA1Context;

void sha1_init(SHA1Context * context) {
  context->h[0] = 0x67452301;
  context->h[1] = 0xEFCDAB89;
  context->h[2] = 0x98BADCFE;
  context->h[3] = 0x10325476;
  context->h[4] = 0xC3D2E1F0;
  context->count[0] = 0;
  context->count[1] = 0;
}


//Process a single 512-bit block
void sha1_transform(SHA1Context *context, const uint8_t block[SHA1_BLOCK_SIZE]) {
  uint32_t w[80];
  uint32_t a,b,c,d,e,temp;
  const uint32_t k[4] = {0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6};
  //prepare message schedule {W_t} 
    for (int i = 0; i < 16; ++i) {
        w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) | (block[i * 4 + 2] << 8) | (block[i * 4 + 3]);
    }
  for (int i = 16; i <80; ++i) {
    w[i] = rotate_left((w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16]),1);
  }

  //Initialize the five working variables a,b,c,d and e with the (i-1) hash value
  a = context->h[0];
  b = context->h[1]; 
  c = context->h[2];
  d = context->h[3];
  e = context->h[4];

  for (uint8_t t = 0; t < 80; ++t) {
    uint32_t k_temp;

    if (t < 20) {
      k_temp = k[0];
      } else if (t < 40) { k_temp = k[1]; 
      } else if (t < 60) { k_temp = k[2] ;
      } else { k_temp = k[3]; } 
     
    temp = rotate_left(a,5) + sha1_f(t , b, c, d) + e + k_temp + w[t];
    e = d;
    d = c;
    c = rotate_left(b,30);
    b = a;
    a = temp;

  }

  //Update the hash values
  context->h[0] += a;
  context->h[1] += b;  
  context->h[2] += c;
  context->h[3] += d;
  context->h[4] += e;
}

void sha1_update(SHA1Context *context, const uint8_t *data, size_t len) {
  size_t index = (context->count[0] >> 3) & 63;
  size_t part_len = 64 - index;
  size_t i;

  //Update the bit count
  context->count[0] += len << 3;
  if (context->count[0] < (len << 3)) {
    context->count[1]++;
  }

  context->count[1] += len >> 29;
  
    // If the input data length is larger than the part length, process it in chunks
    if (len >= part_len) {
     // Copy the first part of the data to the buffer
      memcpy(&context->buffer[index], data, part_len);
      // Process the filled buffer
      sha1_transform(context, context->buffer);

      // Process the remaining data in 64-byte blocks
      for (i = part_len; i + 63 < len; i += 64) {
          sha1_transform(context, &data[i]);
      }
      index = 0;
    } else {
        i = 0;
    }

    // Copy the remaining data to the buffer
    memcpy(&context->buffer[index], &data[i], len - i);
}


int main () {
    SHA1Context sha1context;
    uint8_t digest[SHA1_DIGEST_SIZE];
    uint8_t message[] = "The quick brown fox jumps over the lazy dog";
    size_t length = sizeof(message) - 1;

    size_t padded_length = 512;
    uint8_t *padded_message = (uint8_t *)malloc(padded_length);

    sha1_init(&sha1context);
    sha1_pad(message, length, &padded_message, &padded_length);

    sha1_update(&sha1context, padded_message, padded_length);

    // Free dynamically allocated memory
    free(padded_message);
	
    printf("SHA-1 hash: ");
    for (int i = 0; i < SHA1_DIGEST_SIZE; ++i) {
        digest[i] = (sha1context.h[i >> 2] >> ((3 - (i & 3)) * 8)) & 0xFF;
        printf("%02x", digest[i]);
    }

    printf("\n");
    return 0;
}
