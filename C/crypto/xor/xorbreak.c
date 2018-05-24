#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "binrep.h"
#include "binrep-util.h"
#include "binmanip.h"
#include "textscore.h"

#define BUFFER_DELTA 64

size_t base64f2bin (const char *filename, uint8_t **outptr)
{
    FILE *file = fopen (filename, "r");
    if (!file)
        return 0;

    size_t out_size = 0;
    uint8_t *out = NULL;

    size_t read;
    char *line = NULL;
    size_t length = 0;

    while ((read = getline(&line, &length, file)) != -1)
    {
        uint8_t *buffer;
        size_t size = base64s2binb (line, &buffer);

        // This can be optimized
        if (size != 0)
        {
            out = buffer_append (out, out_size, buffer, size);
            out_size += size;
        }
    }

    fclose(file);

    *outptr = out;
    return out_size;
}

size_t hexf2bin (const char *filename, uint8_t **outptr)
{
    FILE *file = fopen (filename, "r");
    if (!file)
        return 0;

    size_t out_size = 0;
    uint8_t *out = NULL;

    size_t read;
    char *line = NULL;
    size_t length = 0;

    while ((read = getline(&line, &length, file)) != -1)
    {
        uint8_t *buffer;
        size_t size = hexs2binb (line, &buffer);

        // This can be optimized
        if (size != 0)
        {
            out = buffer_append (out, out_size, buffer, size);
            out_size += size;
        }
    }

    fclose(file);

    *outptr = out;
    return out_size;
}

void bin2f (const char *filename, uint8_t *buffer, size_t size)
{
    FILE *file = fopen (filename, "wb");

    if (file)
    {
        fwrite (buffer, sizeof(uint8_t), size, file);
        fclose (file);
    }
}

uint8_t find_xor_decode (uint8_t *buffer, size_t size)
{
    double max_score = -INFINITY;
    uint8_t key;

    for (int i = 0; i < 256; i++)
    {
        uint8_t *xored = xorcbb (buffer, size, i);



        double score = plaintext_score (xored, size);

        if (score > max_score)
        {
            //printf ("key: %ld\n", i);
            //buffer_print (xored, size);

            key = i;
            max_score = score;
        }

        free (xored);
    }

    return key;
}

double hamming_test (uint8_t *buffer, size_t size, size_t num, size_t len)
{
    if (num * len > size)
        return +INFINITY;

    size_t sum = 0.0;

    for (size_t x = 0; x < num; x++)
    {
        for (size_t y = 0; y < num; y++)
        {
            sum += hamming_dist (buffer + x * len, buffer + y * len, len);
        }
    }

    return (double) sum / len;
}


int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        printf ("Usage: %s infile outfile\n", argv[0]);
        puts ("Reads in a base64 encoded file. Tried to find a key for xor-chiffre.");
        puts ("Best guess is used to decode the file.");
        return 0;
    }

    uint8_t *buffer;
    size_t size = base64f2bin (argv[1], &buffer);
    if (size == 0)
    {
        puts ("Could not read file.");
        return 0;
    }

    double minDist = +INFINITY;
    size_t bestLength;

    for (size_t k = 1; k < 40; k++)
    {
        double dist = hamming_test (buffer, size, 20, k);

        if (dist < minDist)
        {
            minDist = dist;
            bestLength = k;
        }
    }

    printf ("smallest length: %ld, distance: %f\n", bestLength, minDist);

    //bestLength = 9;

    uint8_t *bufs[bestLength];
    size_t bufssz[bestLength];

    buffer_transpose_split (buffer, size, bestLength, bufs, bufssz);

    uint8_t key[bestLength + 1];

    for (size_t k = 0; k < bestLength; k++)
    {
        key[k] = find_xor_decode (
            bufs[k], bufssz[k]
        );
    }
    key[bestLength] = '\0';

    printf ("key found: %s\n", key);

    xorbr (buffer, size, key, bestLength);

    printf ("Output written to: %s\n", argv[2]);

    bin2f (argv[2], buffer, size);

    return 0;
}
