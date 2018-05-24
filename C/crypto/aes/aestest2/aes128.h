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
        const uint8_t *word = data + 4 * k;

        block[k] =
            word[0] <<  0 |
            word[1] <<  8 |
            word[2] << 16 |
            word[3] << 24;
    }
}

static
void aes128_write_block (uint8_t *data, const uint32_t *block)
{
    for (int k = 0; k < 4; k++)
    {
        uint32_t word = block[k];
        uint8_t *pdata = data + 4 * k;

        pdata[0] = word >>  0;
        pdata[1] = word >>  8;
        pdata[2] = word >> 16;
        pdata[3] = word >> 24;
    }
}


extern const uint32_t aes_tbox [256];
#endif
