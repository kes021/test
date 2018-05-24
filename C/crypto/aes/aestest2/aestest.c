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

uint32_t rol32 (uint32_t v, uint8_t s)
{
    return ( v << s ) | ( v >> (32 - s));
}

uint32_t tbox_mix_columns (uint32_t c, const uint32_t *tbox)
{
    printf ("tbox_mix_columns (%08x)\n", c);
    puts ("Note that words are in the wrong order.");

    printf ("tbox[%02x] = %08x\n", (c >>  0) & 0xff, tbox [(c >>  0) & 0xff]);
    uint32_t t1 = rol32(tbox [(c >>  0) & 0xff], 0);
    printf ("t1 = %08x\n", t1);

    printf ("tbox[%02x] = %08x\n", (c >>  8) & 0xff, tbox [(c >>  8) & 0xff]);
    uint32_t t2 = rol32(tbox [(c >>  8) & 0xff], 8);
    printf ("t2 = %08x\n", t2);

    printf ("tbox[%02x] = %08x\n", (c >> 16) & 0xff, tbox [(c >> 16) & 0xff]);
    uint32_t t3 = rol32(tbox [(c >> 16) & 0xff], 16);
    printf ("t3 = %08x\n", t3);

    printf ("tbox[%02x] = %08x\n", (c >> 24) & 0xff, tbox [(c >> 24) & 0xff]);
    uint32_t t4 = rol32(tbox [(c >> 24) & 0xff], 24);
    printf ("t4 = %08x\n", t4);

    printf ("%08x\n", t1);
    printf ("%08x\n", t1 ^ t2);
    printf ("%08x\n", t1 ^ t2 ^ t3);
    printf ("%08x\n", t1 ^ t2 ^ t3 ^ t4);
    putchar ('\n');

    return t1 ^ t2 ^ t3 ^ t4;
}

static inline
void aes128_mix_columns (uint32_t *state)
{
    print_block (state);
    state[0] = tbox_mix_columns (state[0], aes_tbox);
    print_block (state);
    state[1] = tbox_mix_columns (state[1], aes_tbox);
    print_block (state);
    state[2] = tbox_mix_columns (state[2], aes_tbox);
    print_block (state);
    state[3] = tbox_mix_columns (state[3], aes_tbox);
    print_block (state);
}


int main (int argc, char *argv[])
{

    printf ("%08x\n", 0x12345678 << 0);
    printf ("%08x\n", 0x12345678 >> 32);

    uint8_t *key_test_string = (uint8_t*) "\x2b\x7e\x15\x16\x28\xae\xd2\xa6\xab\xf7\x15\x88\x09\xcf\x4f\x3c";

    uint32_t key[4], w[4 * 11];

    aes128_load_block (key, key_test_string);
    aes128_key_expand (key, w);

    puts ("key schedule:");
    for (int k = 0; k < 4 * 11; k++)
    {
        printf ("w[%2d] =\t", k);
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


    puts ("MixColumns test");

    uint8_t *m_col_string = (uint8_t*) "\x63\x53\xe0\x8c\x09\x60\xe1\x04\xcd\x70\xb7\x51\xba\xca\xd0\xe7";
    uint32_t m_col[4];

    aes128_load_block (m_col, m_col_string);
    print_block (m_col);
    putchar ('\n');
    aes128_mix_columns (m_col);
    putchar ('\n');
    print_block (m_col);

    return 0;
}
