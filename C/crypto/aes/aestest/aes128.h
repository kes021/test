#ifndef AES_128_H
#define AES_128_H
#include <stdint.h>

/*
 *  This is optimized for little end.
 *  the value s0s1s2s3 is represented in the register as
 *  s3s2s1s0. Thus there are some implications on how to
 *  shiftRows works.
 */

void aes128_key_expand (uint32_t *key, uint32_t *w);

void aes128_block_encrypt (uint32_t *plain, uint32_t *w, uint32_t *chiff);
void aes128_block_decrypt (uint32_t *chiff, uint32_t *w, uint32_t *plain);

static
void aes128_load_block (uint32_t *block, const uint8_t *data)
{
    for (int k = 0; k < 4; k++)
    {
        block[k] =
            (data[4 * k + 0] <<  0) |
            (data[4 * k + 1] <<  8) |
            (data[4 * k + 2] << 16) |
            (data[4 * k + 3] << 24);
    }
}

static
void aes128_write_block (uint8_t *data, const uint32_t *block)
{
    for (int k = 0; k < 4; k++)
    {
        data [4 * k + 0] = (block[k] >>  0) & 0xff;
        data [4 * k + 1] = (block[k] >>  8) & 0xff;
        data [4 * k + 2] = (block[k] >> 16) & 0xff;
        data [4 * k + 3] = (block[k] >> 24) & 0xff;
    }
}

#endif
