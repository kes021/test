#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "binrep.h"
#include "aes128.h"



/*
 *  Used to print a block in memory.
 */
static
void print_word (uint32_t w)
{
    printf ("%02x", (w >>  0) & 0xff);
    printf ("%02x", (w >>  8) & 0xff);
    printf ("%02x", (w >> 16) & 0xff);
    printf ("%02x", (w >> 24) & 0xff);
}

static
void print_block (uint32_t *block)
{
    for (int k = 0; k < 4; k++)
    {
        print_word (block[k]);
    }

    putchar ('\n');
}


int main (int argc, char *argv[])
{

    uint8_t *key_test_string = (uint8_t*) "\x2b\x7e\x15\x16\x28\xae\xd2\xa6\xab\xf7\x15\x88\x09\xcf\x4f\x3c";

    uint32_t key[4], w[4 * 11];

    aes128_load_block (key, key_test_string);
    aes128_key_expand (key, w);

    puts ("key schedule:");
    for (int k = 0; k < 4 * 11; k++)
    {
        printf ("w[%2d] = \t", k);
        print_word (w[k]);
        putchar ('\n');
    }
    putchar ('\n');

    uint8_t *key_string     = (uint8_t*) "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f";
    uint8_t *plain_string   = (uint8_t*) "\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xaa\xbb\xcc\xdd\xee\xff";

    uint32_t plain[4], chiff[4];

    aes128_load_block (key, key_string);
    aes128_key_expand (key, w);

    aes128_load_block (plain, plain_string);

    aes128_block_encrypt (plain, w, chiff);
    putchar ('\n');
    aes128_block_decrypt (chiff, w, plain);
    putchar ('\n');


    uint8_t output[16];

    aes128_write_block (output, plain);
    for (int k = 0; k < 16; k++)
        printf ("%02x", output[k]);
    putchar ('\n');

    aes128_write_block (output, chiff);
    for (int k = 0; k < 16; k++)
        printf ("%02x", output[k]);
    putchar ('\n');


    return 0;
}
