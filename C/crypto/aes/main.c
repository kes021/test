#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "aes.h"

void str2block (const uint8_t *str, uint32_t key[4])
{
    for (int k = 0; k < 4; k++)
    {
        key[k] =
            (str[4 * k + 0] <<  0) |
            (str[4 * k + 1] <<  8) |
            (str[4 * k + 2] << 16) |
            (str[4 * k + 3] << 24);
    }
}

static
void print_block (uint32_t *block)
{
    uint8_t *_block = (uint8_t *) block;

    for (int i = 0; i < 16; i++)
    {
        printf ("%02x", _block[i]);
    }
    putchar ('\n');
}

static
void print_block_ascii (uint32_t *block)
{
    uint8_t *_block = (uint8_t *) block;

    for (int i = 0; i < 16; i++)
    {
        printf ("%c", _block[i]);
    }
    putchar ('\n');
}



int main (int argc, char *argv[])
{
    // Blocks for the key, plaintext and chiffretext
    uint32_t key[4], plain[4], chiff[4];

    // expanded keys
    uint32_t w[4 * 11];

    str2block ("YELLOW SUBMARINE", key);
    aes128_key_expand (key, w);


    str2block ("\x5e\x7f\x7d\x53\xdf\x12\x2b\x7a\xf3\x15\x56\xe5\xfe\x67\x7f\x99", chiff);

    print_block (chiff);

    aes128_block_decrypt (chiff, w, plain);

    print_block_ascii (plain);

    return 0;
}
