#include <stdio.h>
#include <stdlib.h>
#include "encoding.h"








/*
 *  the main function
 */
int main (int argc, char *argv[])
{
/*
    uint8_t* bin_string;
    size_t bin_size = 32;

    bin_string = (uint8_t*) malloc(32);
    if (bin_string == NULL)
    {
        printf("Memory Allocation Error\n");
        return 0;
    }

    FILE *f;
    f = fopen(argv[1], "rb");
    if (!f)
    {
        printf("File Error\n");
        return 0;
    }

    fread (bin_string, 32, 1, f);
    size_t i = 1;
    int buf[32];
    while (fread (buf, 32, 1, f) == 1)
    {
        i++;
        uint8_t* temp = realloc(bin_string, 32 * i);
        if (temp == NULL)
        {
            free(bin_string);
            printf("Memory Allocation Error\n");
            return 0;
        }
        bin_string = temp;

        for (size_t k = 0; k < 32; k++)
        {
            bin_string[32*(i-1) + k] = buf[k];
        }
    }
    if (i != 1)
        bin_size = 32 * (i-1);
    print_bin(bin_string, bin_size);

    char* hex_string;
    hex_string = bin_to_hex(bin_string, bin_size);
    print_hex(hex_string, 2 * bin_size);


    char hex_string[] = "AA";
    bin_string = hex_to_bin (hex_string, 2);
    print_hex(hex_string, 2);
    print_bin(bin_string, 1);
*/
/*
    char base64_string[] = "Aa45y90+";
    size_t size = 8;

    uint8_t* bin_string;
    bin_string = base64_to_bin(base64_string, size);
    if (bin_string == NULL)
    {
        printf("Error\n");
        return 0;
    }

    print_bin(bin_string, 6);
    print_base64 (base64_string, 8);

    char* base64_string2 = bin_to_base64(bin_string, 3*size/4);
    if (base64_string2 == NULL)
    {
        printf("Error\n");
        return 0;
    }
    print_base64 (base64_string2, size);
*/

    char hex_string[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    size_t hex_size = sizeof(hex_string) - 1;

    uint8_t* bin_string = hex_to_bin (hex_string, hex_size);
    if (bin_string == NULL)
    {
        printf("Error\n");
        return 0;
    }

    size_t bin_size = hex_size / 2;
    char* base64_string = bin_to_base64(bin_string, bin_size);
    if (base64_string == NULL)
    {
        printf("Error\n");
        return 0;
    }
    if (bin_size % 3 == 0)
        print_base64 (base64_string, 4*bin_size /3);
    else
        print_base64 (base64_string, 4*(bin_size /3 +1));


    free(bin_string);
    bin_string = base64_to_bin(base64_string, 4*bin_size/3);
    if (bin_string == NULL)
    {
        printf("Error\n");
        return 0;
    }
    char *hex_string2 = bin_to_hex (bin_string, bin_size);
    if (hex_string2 == NULL)
    {
        printf("Error\n");
        return 0;
    }
    print_hex(hex_string2, hex_size);

    print_bin(bin_string, bin_size);

    free(hex_string2);
    free(bin_string);
    free(base64_string);


    return 0;
}
