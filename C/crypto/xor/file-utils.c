#include <stdio.h>
#include <ctype.h>
#include "file-utils.h"

size_t fread_buffer_ignore_space (char *buffer, size_t size, FILE *file)
{
    size_t offset = 0;

    while (!feof(file) && offset < size)
    {
        int c = fgetc (file);

        if (!isspace (c))
            buffer[offset++] = c;
    }

    return offset;
}
