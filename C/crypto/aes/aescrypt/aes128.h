#ifndef AES_128_H
#define AES_128_H
#include <stdint.h>

/*
 *  Given the aes-key, this function expands the key to full length, depending on
 *  the key and block size.
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
            (data[4 * k + 3] <<  0) |
            (data[4 * k + 2] <<  8) |
            (data[4 * k + 1] << 16) |
            (data[4 * k + 0] << 24);
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
