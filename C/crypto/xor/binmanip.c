#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "binmanip.h"



uint8_t *buffer_clone (const uint8_t *buffer, size_t size)
{
    uint8_t *r = malloc (size);

    if (r)
        memcpy (r, buffer, size);

    return r;
}

uint8_t *buffer_append (uint8_t *buffer, size_t size, const uint8_t *append, size_t append_size)
{
    uint8_t *r = realloc (buffer, size + append_size);

    if (!r)
        return NULL;

    memcpy (r + size, append, append_size);

    return r;
}

void buffer_print (uint8_t *buffer, size_t size)
{
    for (size_t k = 0; k < size; k++)
        putchar (buffer[k]);
    putchar ('\n');
}

void xorb (uint8_t *dest, const uint8_t* op, size_t size)
{
    for (size_t k = 0; k < size; k++)
        dest[k] = dest[k] ^ op[k];
}

void xorbb (uint8_t *dest, size_t size, uint8_t b)
{
    for (size_t k = 0; k < size; k++)
        dest[k] = dest[k] ^ b;
}

void xorbr (uint8_t *dest, size_t size, uint8_t *key, size_t keysz)
{
    for (size_t k = 0; k < size; k++)
        dest[k] = dest[k] ^ key[k % keysz];
}

void xorbro (uint8_t *dest, size_t size, uint8_t *key, size_t keysz, size_t offset)
{
    for (size_t k = 0; k < size; k++)
        dest[k] = dest[k] ^ key[(k + offset) % keysz];
}

uint8_t *xorcb (const uint8_t *src, const uint8_t* op, size_t size)
{
    uint8_t *r = malloc (size);

    if (!r)
        return NULL;

    for (size_t k = 0; k < size; k++)
        r[k] = src[k] ^ op[k];

    return r;
}

uint8_t *xorcbb (const uint8_t *src, size_t size, uint8_t b)
{
    uint8_t *r = malloc (size);

    if (!r)
        return NULL;

    for (size_t k = 0; k < size; k++)
        r[k] = src[k] ^ b;

    return r;
}

uint8_t *xorcbr (const uint8_t *src, size_t size, uint8_t *key, size_t keysz)
{
    uint8_t *r = malloc (size);

    if (!r)
        return NULL;

    for (size_t k = 0; k < size; k++)
        r[k] = src[k] ^ key[k % keysz];

    return r;
}



#ifdef __builtin_popcount
#define bitcount __builtin_popcount
#else
static
size_t bitcount (uint8_t b)
{

    size_t c = 0;

    while (b)
    {
        if (b & 0x01)
            c++;
        b = b >> 1;
    }

    return c;
}
#endif

size_t hamming_dist (const uint8_t *a, const uint8_t *b, size_t size)
{
    size_t dist = 0;

    for (size_t k = 0; k < size; k++)
    {
        uint8_t x =  a[k] ^ b[k];

        dist += bitcount (x);
    }

    return dist;
}

void buffer_transpose_split (const uint8_t *buffer, size_t size, size_t split, uint8_t *out[], size_t outsz[])
{
    size_t dsize = (size % split == 0) ? size / split : size / split + 1;

    // allocate buffers of given size
    for (size_t k = 0; k < split; k++)
    {
        out[k]      = malloc (dsize);
        outsz[k]    = 0;
    }

    for (size_t k = 0; k < size; k++)
    {
        out[k % split][outsz[k % split]++] = buffer[k];
    }
}
