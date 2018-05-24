#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>



/*
 * takes a string buffer and its size
 * hash is then updated by the hash of this buffer string
 */
void make_hash (uint8_t *buffer, size_t size, uint8_t *hash);

/*
 * sets the entries of sha_W (array of size 80) to 0
 */
void initialize_zero (uint32_t *sha_W);

/*
 * sets the initial constants given in sha-1 algorithm
 */
void set_initial_H (uint32_t *sha_H);

/*
 * puts the next 512 of buffer into block while
 * padding if factor * offset > size
 * block is an array of length 64
 */
void get_next_block (uint8_t *buffer, size_t offset, uint8_t *block);

/*
 * divides the block into 16 parts of 16 bits saved into the first
 * 16 entries of the array W
 * W is an array of length 80
 * block is an array of length 64
 */
void divide_block (uint32_t *sha_W, uint8_t *block);

/*
 * runs sha1 - hash algorithm part (b) to (d)
 * W is an array of length 80
 * hash is an array of length ??
 */
void compute (uint32_t *sha_W, uint32_t *sha_H);

/*
 * computes the entries 16 to 79 of W using the sha-1 function
 */
void set_W (uint32_t *sha_W);

/*
 * one of the sha_1 functions
 */
uint32_t sha_f (int t, uint32_t B, uint32_t C, uint32_t D);

/*
 * another one of the sha_1 functions
 */
uint32_t sha_K (int t);

/*
 * shifts bit v by s to the left
 */
uint32_t rol32 (uint32_t v, int s);

/*
 * pad gets the last block (after 64 * (offset+1) > size)
 * returns 0 if only one 64-bit block is necessary, in that case the block is completely saved in block
 * returns 1 if two 64-bit blocks are necessary, in which case block is filled with zeros, in the second
 *    phase the length is put in the end and the corresponding first bits are filled with zeros
 */
int pad (uint8_t *buffer, size_t size, uint8_t offset, uint8_t *block);

/*
 * this saves the last block in the second case of "pad"
 */
void last_block (size_t size, uint8_t *block);

/*
 * saves sha_H into hash
 */
void put_hash (uint8_t *hash, uint32_t sha_H[5]);

/*
 * prints the buffer in which the hash is saved
 */
void print_hash (uint8_t hash[20]);





void make_hash (uint8_t *buffer, size_t size, uint8_t *hash)
{
    size_t offset = 0;
    uint8_t block[64];          // buffer may have a size > 512 bit
                                // block is used to decompose buffer into 512 bit parts
    uint32_t sha_W[80];
    initialize_zero (sha_W);

    uint32_t sha_H[5];
    set_initial_H (sha_H);

    while (64 * (offset + 1) < size)
    {
        get_next_block (buffer, offset, block);
        divide_block (sha_W, block);
        compute (sha_W, sha_H);

        offset++;
    }
    offset++;

    int last;                // is 0, if only one step is necessary for padding buffer, 1 otherwise
    last = pad (buffer, size, offset, block);

    divide_block (sha_W, block);
    compute (sha_W, sha_H);

    if (last)
    {
        last_block (size, block);
        divide_block (sha_W, block);
        compute (sha_W, sha_H);
    }

    put_hash (hash, sha_H);
}

void initialize_zero (uint32_t *sha_W)
{
    for (int i = 0; i < 80; i++)
        sha_W[i] = 0;
}

void set_initial_H (uint32_t *sha_H)
{
    sha_H[0] = 0x67452301;
    sha_H[1] = 0xEFCDAB89;
    sha_H[2] = 0x98BADCFE;
    sha_H[3] = 0x10325476;
    sha_H[4] = 0xC3D2E1F0;
}

void get_next_block (uint8_t *buffer, size_t offset, uint8_t *block)
{
    for (int i = 0; i < 64; i++)
    {
        block[i] = buffer [64 * offset + i];
    }
}

void divide_block (uint32_t *sha_W, uint8_t *block) // put block into first 16 entries of W
{
    for (int i = 0; i < 16; i++)
    {
/*
        for (int j = 1; j <= 4; j++)
        {
            sha_W[i] ^= ((uint32_t) block[8 * i + j - 1] << (32 - 8 * j));
        }
*/
        sha_W[i] = sha_W[i] ^ (block[8 * i] << 24);
        sha_W[i] = sha_W[i] ^ (block[8 * i + 1] << 16);
        sha_W[i] = sha_W[i] ^ (block[8 * i + 2] << 8);
        sha_W[i] = sha_W[i] ^ (block[8 * i + 3]);
    }
}

void compute (uint32_t *sha_W, uint32_t *sha_H)
{
    uint32_t A = sha_H[0], B = sha_H[1], C = sha_H[2], D = sha_H[3], E = sha_H[4];
    uint32_t temp;
    /*
     * computes the entries 16 to 79 of W using the sha-1 function
     */
    set_W (sha_W);

    for (int t = 0; t < 80; t++)
    {
        temp = rol32 (A, 5) + sha_f (t, B, C, D) + E + sha_W[t] + sha_K (t);
        E = D;
        D = C;
        C = rol32 (B, 30);
        B = A;
        A = temp;
    }

    sha_H[0] += A;
    sha_H[1] += B;
    sha_H[2] += C;
    sha_H[3] += D;
    sha_H[4] += E;
}

uint32_t sha_f (int t, uint32_t B, uint32_t C, uint32_t D)
{
    if (0 <= t && t <= 19)
        return (B & C) | ((~B) & D);
    if (t <= 39)
        return B ^ C ^ D;
    if (t <= 59)
        return (B & C) ^ (B & D) ^ (C & D);
    return B ^ C ^ D;
}

uint32_t sha_K (int t)
{
    if (0 <= t && t <= 19)
        return 0x5A827999;
    if (t <= 39)
        return 0x6ED9EBA1;
    if (t <= 59)
        return 0x8F1BBCDC;
    return 0xCA62C1D6;
}

void set_W (uint32_t *sha_W)
{
    for (int t = 16; t < 80; t++)
    {
        sha_W[t] = rol32 (sha_W[t - 3] ^ sha_W[t - 8] ^ sha_W[t - 14] ^ sha_W[t - 16], 1);
    }
}

uint32_t rol32 (uint32_t v, int s)
{
    if (s % 32 == 0)
        return v;
    return (v << s | v >> (32 - s)) ;
}

int pad (uint8_t *buffer, size_t size, uint8_t offset, uint8_t *block)
{
    int bit_length_size = 0;
    while ((size >> bit_length_size) != 0)
        bit_length_size++;
    int length_size = (bit_length_size / 8) + 1;   // computes the number of bytes needed to rep size

    for (int j = 0; j < size - 64 * (offset - 1); j++)
    {
        block[j] = buffer[64 * (offset - 1) + j];
    }

    if (64 * offset - size >= length_size)  // (64 * offset - size) is the number of bytes left to
    {                                       // write in the current block, length_size is the number
                                            // of bytes needed at the end of the current block to write size
        for (int j = size - 64 * (offset - 1); j < 64 - length_size; j++)
        {
            block[j] = 0;
        }
        for (int j = 64 - length_size; j < 64; j++)
        {
            block[j] = (size >> (8 * (64 - j)) );
        }
        return 0;
    }

    for (int j = 64 * offset - size; j < 64; j++)
    {
        block[j] = 0;
    }

    return 1;
}

void last_block (size_t size, uint8_t *block)
{
    int bit_length_size = 0;
    while ((size >> bit_length_size) != 0)
        bit_length_size++;
    int length_size = (bit_length_size / 8) + 1;   // computes the number of bytes needed to rep size

    for (int j = 0; j < 64 - length_size; j++)
    {
        block[j] = 0;
    }
    for (int j = 64 - length_size; j < 64; j++)
    {
        block[j] = size >> (8 * (64 - j) );
    }
}

void put_hash (uint8_t *hash, uint32_t sha_H[5])
{
    for (int i = 0; i < 5; i++)
    {
        hash[4 * i + 0] = sha_H[i] >> 24;
        hash[4 * i + 1] = sha_H[i] >> 16;
        hash[4 * i + 2] = sha_H[i] >> 8;
        hash[4 * i + 3] = sha_H[i];
    }
}


void print_hash (uint8_t hash[20])
{
    for (int i = 0; i < 20; i++)
    {
        printf("%2.x ", hash[i]);
    }
    printf("\n");
}


int main ()
{
    uint8_t string[0];
    uint8_t hash[20];

    uint32_t H[5];
    set_initial_H (H);

    uint32_t W[80];
    initialize_zero (W);

    compute (W, H);
    put_hash (hash, H);
    print_hash (hash);


    make_hash (string, 0, hash);

    print_hash (hash);

    return 0;
}
