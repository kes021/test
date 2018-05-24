#ifndef BINREPUTIL_H
#define BINREPUTIL_H

/*
 *  Hex-to-Binary and Base64-to-Binary methods.
 *  Convert hexal representations of binary
 *  hexs/base64s expect string represenations and terminate on zero sign
 *  or decode error. Whitespace is ignored.
 *
 *  They return the acutal length written to out.
 */

size_t hex2binb (const char *hex, size_t size, uint8_t **outptr);
size_t hexs2bin (const char *hexs, uint8_t *out, size_t outsz);
size_t hexs2binb (const char *hexs, uint8_t **outptr);

size_t base642binb (const char *base64, size_t size, uint8_t **outptr);
size_t base64s2bin (const char *base64s, uint8_t *out, size_t outsz);
size_t base64s2binb (const char *base64s, uint8_t **outptr);



/*
 *  Binary dump methods.
 *  Take a binary buffer (binb) and dump it into a memory (hex/base64)
 *  or create a string (hexs/base64s) and return it.
 *
 *  Be sure that the output buffer contains enough space.
 *  hex:    2 * size
 *  base64: 4 * ceil(size / 3)
 */
char *binb2hexs (const uint8_t *buffer, size_t size);
char *binb2base64s (const uint8_t *buffer, size_t size);


#endif
