#include <stdlib.h>
#include <string.h>
#include "binrep.h"

size_t hex2binb (const char *hex, size_t size, uint8_t **outptr)
{
    *outptr = NULL;

    // allocate space for the maximal number of bytes written
    size_t outsz = size / 2 + 1;

    uint8_t *out = malloc (outsz);
    if (!out)
        return 0;

    size_t written;

    hex2bin (hex, size, out, outsz, &written, NULL);

    *outptr = out;
    return written;
}

size_t hexs2bin (const char *hexs, uint8_t *out, size_t outsz)
{
    size_t written;

    hex2bin (hexs, strlen (hexs), out, outsz, &written, NULL);
    return written;
}

size_t hexs2binb (const char *hexs, uint8_t **outptr)
{
    return hex2binb (hexs, strlen(hexs), outptr);
}

size_t base642binb (const char
 *base64, size_t size, uint8_t **outptr)
{
    *outptr = NULL;

    // allocate space for the maximal number of bytes written
    size_t outsz = 3 * size / 4 + 3;

    uint8_t *out = malloc (outsz);
    if (!out)
        return 0;

    size_t written;
    base642bin (base64, size, out, outsz, &written, NULL);


    *outptr = out;
    return written;
}

size_t base64s2bin (const char *base64s, uint8_t *out, size_t outsz)
{
    size_t written;

    base642bin (base64s, strlen (base64s), out, outsz, &written, NULL);
    return written;
}

size_t base64s2binb (const char *base64s, uint8_t **outptr)
{
    return base642binb (base64s, strlen(base64s), outptr);
}

char *binb2hexs (const uint8_t *buffer, size_t size)
{
    size_t string_size = 2 * size;

    char *string = malloc (string_size + 1);
    if (!string)
        return NULL;

    bin2hex (buffer, size, string, string_size, NULL, NULL);

    string[string_size] = '\0';
    return string;
}

char *binb2base64s (const uint8_t *buffer, size_t size)
{
    size_t string_size = 4 * ( (size % 3) ? size / 3 + 1 : size / 3 );

    char *string = malloc (string_size + 1);
    if (!string)
        return NULL;

    bin2base64 (buffer, size, string, string_size, NULL, NULL);

    string [string_size] = '\0';
    return string;
}
