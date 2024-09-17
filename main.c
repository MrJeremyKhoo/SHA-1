#include <stdio.h>
#include <stdint.h>
#include<string.h>
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

  for (int i = 0; i < 16; ++i) {
    w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) | (block[i * 4 + 2] << 8) | (block[i * 4 + 3]);
  }

  for(int i = 16; i <80; ++i) {
    w[i] = (w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16]);
    uint32_t rotated_w = rotate_left(w[i],1);
  }

}

int main () {
  SHA1Context sha1context;
  SHA1Context* sha1context_ptr = &sha1context;
  sha1_init(sha1context_ptr);
  printf("h1 %08x\n", sha1context.h[0]);

}
