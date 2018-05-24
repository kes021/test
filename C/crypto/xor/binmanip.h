#ifndef BINMANIP_H
#define BINMANIP_H
#include <stddef.h>
#include <stdint.h>

/*
 *  xor buffer operations
 *  xorb, xorbb, xorbr:     xor-buffer, xor-buffer-byte, xor-buffer-repeat
 *  xorcb, xorcbb, xorcbr:  additionally clone buffer
 */
void xorb (uint8_t *dest, const uint8_t* op, size_t size);
void xorbb (uint8_t *dest, size_t size, uint8_t b);
void xorbr (uint8_t *dest, size_t size, uint8_t *key, size_t keysz);
void xorbro (uint8_t *dest, size_t size, uint8_t *key, size_t keysz, size_t offset);



uint8_t *xorcb (const uint8_t *src, const uint8_t* op, size_t size);
uint8_t *xorcbb (const uint8_t *src, size_t size, uint8_t b);
uint8_t *xorcbr (const uint8_t *src, size_t size, uint8_t *key, size_t keysz);

uint8_t *buffer_append (uint8_t *buffer, size_t size, const uint8_t *append, size_t append_size);
uint8_t *buffer_clone (const uint8_t *buffer, size_t size);
void buffer_print (uint8_t *buffer, size_t size);

/*
 *  Buffer transpose split
 *  Splits the buffer in buffers of length split.
 *  Then it transposes these buffer. This results in split count buffer of
 *  the returned size.
 *
 *  out     - pointer to memory that can hold split pointer to a buffer
 *  outsz   - pointer to memory that can hold split size_t of the buffers
 */
void buffer_transpose_split (const uint8_t *buffer, size_t size, size_t split, uint8_t *out[], size_t outsz[]);

size_t hamming_dist (const uint8_t *a, const uint8_t *b, size_t size);

#endif
