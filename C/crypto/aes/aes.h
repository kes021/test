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


#endif
