#include <stdio.h>
#include <stdlib.h>
#include "encoding.h"


int count_value (uint8_t* string, uint8_t x, size_t size)
{
    int count = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (string[i] == x)
            count++;
    }
    return count;
}

uint8_t find_min (double *table)
{
    uint8_t i = 0;
    for (uint8_t k = 0; k < 128; k++)
    {
        if (table[k] < table[i])
        {
            i = k;
        }
    }
    return i;
}


int main (int argc, char *argv[])
{
    double e_expected = 0.12, t_expected = 0.091, a_expected = 0.081;

    char hex_string[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    size_t hex_size = sizeof(hex_string) - 1;
    uint8_t *string = hex_to_bin(hex_string, hex_size);
    if (string == NULL)
    {
        printf("Memory Allocation Error\n");
        return 0;
    }
    size_t size = hex_size/2;
    printf("%zu\n", size);

    double table[128];

    for (uint8_t i = 0; i < 128; i++)
    { /// change the e_observed stuff here!!
        double e_observed = (double)count_value(string, i, size) / (double)size;
        double t_observed = (double)count_value(string, i, size) / (double)size;
        double a_observed = (double)count_value(string, i, size) / (double)size;
        table[i] = ((e_observed - e_expected) * (e_observed - e_expected)) / e_expected
            + ((t_observed - t_expected) * (t_observed - t_expected)) / t_expected
            + ((a_observed - a_expected) * (a_observed - a_expected)) / a_expected;
    }

    uint8_t min = find_min(table);

    string = xor_const(string, min, size);

    print_string(string, size);

    free(string);
    return 0;
}
