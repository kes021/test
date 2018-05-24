#include <stdio.h>
#include <stdlib.h>
#include "encoding.h"


uint8_t* xor_ (uint8_t* string1, uint8_t* string2, size_t size)
{
    uint8_t* out;
    out = (uint8_t*) malloc(size);
    if (out == NULL)
    {
        printf("Memory Allocation Error\n");
        return NULL;
    }

    for (size_t i = 0; i < size; i++)
    {
        out[i] = string1[i] ^ string2[i];
    }
    return out;
}



int main (int argc, char *argv[])
{
    char hex_string1[] = "1c0111001f010100061a024b53535009181c";
    char hex_string2[] = "686974207468652062756c6c277320657965";
    size_t size = sizeof(hex_string1) - 1;

    uint8_t *bin_string1, *bin_string2, *bin_xor;
    bin_string1 = hex_to_bin(hex_string1, size);
    bin_string2 = hex_to_bin(hex_string2, size);
    if (bin_string1 == NULL || bin_string2 == NULL)
    {
        return 0;
    }

    size_t bin_size = size / 2;
    bin_xor = xor_(bin_string1, bin_string2, bin_size);

    char *hex_xor = bin_to_hex(bin_xor, bin_size);
    if (hex_xor == NULL)
    {
        return 0;
    }

    print_hex(hex_xor, size);

    free(hex_xor);
    free(bin_string1);
    free(bin_string2);
    free(bin_xor);

    return 0;
}
