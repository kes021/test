#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void print_block (const uint8_t *block)
{
    for (int i = 0; i < 64; i++)
    {
        printf("%02x ", block[i]);
    }
    putchar('\n');
}


void print_hash (uint8_t *ar)
{
    for (int i = 0; i < 20; i++)
    {
        printf ("%02x", ar[i]);
    }
    putchar('\n');
}

void put_hash (uint32_t H[5], uint8_t hash[20])
{
    for (int i = 0; i < 5; i++)
    {
        hash[4 * i] = H[i] >> 24;
        hash[4 * i + 1] = H[i] >> 16;
        hash[4 * i + 2] = H[i] >> 8;
        hash[4 * i + 3] = H[i];
    }
}


void load_block (uint8_t *out, const uint8_t *in, size_t offset)
{
    for (int i = 0; i < 64; i++)
    {
        out[i] = in[64 * offset + i];
    }
}


uint32_t K (int t)
{
    if (0 <= t && t <= 19)
    {
        return 0x5A82799;
    }
    if (t <= 39)
    {
        return 0x6ED9EBA1;
    }
    if (t <= 59)
    {
        return 0x8F1BBCDC;
    }
    if (t <= 79)
    {
        return 0xCA62C1D6;
    }
    return 0xFFFFFFFF;
}


uint32_t f (int t, uint32_t B, uint32_t C, uint32_t D)
{
    if (0 <= t && t <= 19)
    {
        return (B & C) | ((~B) & D);
    }
    if (t <= 39)
    {
        return B ^ C ^ D;
    }
    if (t <= 59)
    {
        return (B & C) | (B & D) | (C & D);
    }
    if (t <= 79)
    {
        return B ^ C ^ D;
    }
    return 0xFFFFFFFF;
}

uint32_t rol32 (uint32_t v, int s)
{
    s = s % 32;
    if (s == 0)
        return v;
    return ( v << s ) | ( v >> (32 - s));
}


/*
 * W is a pointer of length 80 with the first 16 initialized
 */

void do_round (uint32_t *W, uint32_t *H)
{
    for (int t = 16; t < 80; t++)
    {
        W[t] = rol32 (W[t-3] ^ W[t-8] ^ W[t -14] ^ W[t - 16], 1);
    }

    uint32_t A = H[0], B = H[1], C = H[2], D = H[3], E = H[4], temp;

    for (int t = 0; t < 80; t++)
    {
        temp = rol32 (A, 5) + f(t, B, C, D) + E + W[t] + K(t);
        E = D;
        D = C;
        C = rol32 (B, 30);
        B = A;
        A = temp;
    }

    H[0] += A;
    H[1] += B;
    H[2] += C;
    H[3] += D;
    H[4] += E;
}


/*
 *  block is a 64-byte block
 *  it is divided into 4 byte parts that are saved as one word
 */

void divide_block (const uint8_t *block, uint32_t *words)
{
    uint32_t buf;
    for (int i = 0; i < 16; i++)
    {
        words[i] = 0;

        buf = block[4 * i];
        words[i] = words[i] | (buf << 24);

        buf = block[4 * i + 1];
        words[i] = words[i] | (buf << 16);

        buf = block[4 * i + 2];
        words[i] = words[i] | (buf << 8);

        buf = block[4 * i + 3];
        words[i] = words[i] | buf;
    }
}


void do_block (const uint8_t *block, uint32_t *words, uint32_t *H)
{

    print_block (block);


    divide_block (block, words);
    do_round (words, H);
}



/*
 *  sets the initial values of the Hash in SHA-1
 *  H is an array of length 5
 */

void set_initial_value (uint32_t *H)
{
    H[0] = 0x67452301;
    H[1] = 0xEFCDAB89;
    H[2] = 0x98BADCFE;
    H[3] = 0x10325476;
    H[4] = 0xC3D2E1F0;
}




/*
 *  Computes the sha1-hash of the given data.
 *  buffer - pointer to the input data
 *  size - size of data pointed to by buffer
 *  hash - pointer to memory of at least 20 byte receiving the final hash
 */

void sha1 (uint8_t *buffer, size_t size, uint8_t *hash)
{
    size_t offset = 0;
    uint8_t block[64];

    uint32_t W[80];
    uint32_t H[5];

    uint64_t size_ =  8 * (uint64_t) size;

    set_initial_value (H);


    while (offset + 64 < 8 * size)
    {
        load_block (block, buffer, offset);
        do_block (block, W, H);
        offset += 64;
    }

    // last block
    if (8 * size - offset > 8)
    {
        for (int i = 0; i < 8 * size - offset; i++)
        {
            block[i] = buffer[64 * offset + i];
        }
        block[8 * size - offset + 1] = 0x80;
        for (int i = 8 * size - offset + 2; i < 56; i++)
        {
            block[i] = 0;
        }
        for (int i = 1; i <= 8; i++)
        {
            block[64 - i] = (size_ >> (64 - 8 * i));
        }
        do_block (block, W, H);
        put_hash (H, hash);
        return;
    }

    if (8 * size - offset == 0)
    {
        if (size != 0)
        {
            load_block (block, buffer, offset);
            do_block (block, W, H);
        }
        block[0] = 0x80;
        for (int i = 1; i < 56; i++)
        {
            block[i] = 0;
        }
        for (int i = 1; i <= 8; i++)
        {
            block[64 - i] = (size_ >> (64 - 8 * i));
        }
        do_block (block, W, H);
        put_hash (H, hash);
        return;
    }

    // if ( 1 <= size - offset <= 8 ) in this case the 1 is put in the last block which contains parts of
    // the message, but the length is in a new last block, as the size does not fit at the end of the previous
    // block

    for (int i = 0; i < 8 * size - offset; i++)
    {
        block[i] = buffer[64 * offset + i];
    }
    block[size - offset] = 0x80;
    for (int i = 8 * size - offset + 1; i < 64; i++)
    {
        block[i] = 0;
    }
    do_block (block, W, H);

    for (int i = 0; i < 56; i++)
    {
        block[i] = 0;
    }
    for (int i = 1; i <= 8; i++)
    {
        block[64 - i] = (size_ >> (64 - 8 * i));
    }
    do_block (block, W, H);
    put_hash (H, hash);
}





int main (int argc, char *argv[])
{
    uint8_t message[0];
    size_t size = 0;
    uint8_t hash[20];

    sha1 (message, size, hash);
    print_hash (hash);

    return 0;
}





