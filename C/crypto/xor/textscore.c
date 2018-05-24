#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "binmanip.h"
#include "textscore.h"

bool is_garbage (uint8_t c)
{
    if (c >= 0x20 && c <= 0x7F)
        return false;

    return c != '\t' && c != '\n' && c != '\r';
}


double plaintext_score (uint8_t *buffer, size_t size)
{
    // None printable characters are not contained in plaintext
    // many small letters and spaces, some big letters
    double score = .0;


    for (size_t k = 0; k < size; k++)
    {
        uint8_t c = buffer[k];

        if (is_garbage (c))
            score -= 9. / size;

        else if (strchr ("aeiou", c))
            score += 4.5 / size;

        else if (c >= 'a' && c <= 'z')
            score += 3. / size;

        else if (c >= 'A' && c <= 'B')
            score += 2.5 / size;

        else if (strchr ("\x20!?:;.,", c))
            score += 1.5 / size;

        else
            score += 1. / size;
    }

    return score;
}
