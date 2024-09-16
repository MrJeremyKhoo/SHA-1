#include <stdio.h>
#include <stdint.h>
#include<string.h>

#define SHA1_BLOCK_SIZE 64
#define SHA1_DIGEST_SIZE 20

typedef struct {
  uint32_t h[5];
  uint32_t count[2];
  uint8_t buffer[SHA1_BLOCK_SIZE];
} SHA1Context

void sha1_init(SHA1Context * context) {
  context->h[0] = 0x67452301;
  context->h[1] = 0xEFCDAB89;
  context->h[2] = 0x98BADCFE;
  context->h[3] = 0x10325476;
  context->h[4] = 0xC3D2E1F0;
  
  context->count[0] = 0;
  context->count[1] = 0;
}
