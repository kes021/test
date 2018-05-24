#ifndef BINREP_H
#define BINREP_H
#include <stddef.h>
#include <stdint.h>

/*
 *   const char *in,             // pointer to buffer containing hexadecimal representation
 *   size_t in_size,             // size of input buffer in bytes
 *
 *   uint8_t *out,               // pointer to buffer to receive the binary output
 *   size_t out_max_size,        // max size of the output buffer
 *
 *   size_t *ptr_bytes_written,  // [optional] receives the number of bytes written
 *   size_t *ptr_bytes_read      // [optional] receives the number of bytes read
 */


void hex2bin (const char *in, size_t in_size, uint8_t *out, size_t out_max_size,
    size_t *ptr_bytes_written, size_t *ptr_bytes_read);

void bin2hex (const uint8_t *in, size_t in_size, char *out, size_t out_max_size,
    size_t *ptr_bytes_written, size_t *ptr_bytes_read);

void base642bin (const char *in, size_t in_size, uint8_t *out, size_t out_max_size,
    size_t *ptr_bytes_written, size_t *ptr_bytes_read);

void bin2base64 (const uint8_t *in, size_t in_size, char *out, size_t out_max_size,
    size_t *ptr_bytes_written, size_t *ptr_bytes_read);


#endif
