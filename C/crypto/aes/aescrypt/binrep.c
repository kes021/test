#include <stddef.h>
#include <stdint.h>
#include "binrep.h"

static
char val2hexc (uint8_t value)
{
    static const char *hexmap = "0123456789abcdef";

    if (value < 16)
        return hexmap[value];

    return 0;
}

static
uint8_t hexc2val (char c)
{
    if ('0' <= c && c <= '9')
        return c - '0';
    c &= 0xdf;  // clear 6th bit

    if ('A' <= c && c <= 'F')
        return c - 'A' + 0x0A;

    return 0xFF;    // invaild
}

static
char val2base64c (uint8_t value)
{
    if (value < 0x1A)
        return 'A' + value;
    if (value < 0x34)
        return 'a' + value - 0x1A;
    if (value < 0x3E)
        return '0' + value - 0x34;
    if (value == 0x3E)
        return '+';
    if (value == 0x3F)
        return '/';

    return '\0';
}

static
uint8_t base64c2val (char c)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A';
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 0x1A;
    if (c >= '0' && c <= '9')
        return c - '0' + 0x34;
    if (c == '+')
        return 0x3E;
    if (c == '/')
        return 0x3F;
    if (c == '=')
        return 0;   // special char

    return 0xFF;    // decode error
}

void hex2bin (const char *in, size_t in_size, uint8_t *out, size_t out_max_size,
    size_t *ptr_bytes_written, size_t *ptr_bytes_read)
{
    size_t offset = 0, written = 0;

    while (offset + 1 < in_size && written < out_max_size)
    {
        uint8_t c1 = hexc2val (in[offset++]);
        uint8_t c2 = hexc2val (in[offset++]);

        if (c1 == 0xFF || c2 == 0xFF)
            break;  // corrupted data input

        out[written++] = ( c1 << 4 ) | c2;
    }

    if (ptr_bytes_written)
        *ptr_bytes_written = written;

    if (ptr_bytes_read)
        *ptr_bytes_read = offset;
}

void bin2hex (
    const uint8_t *in, size_t in_size, char *out, size_t out_max_size,
    size_t *ptr_bytes_written, size_t *ptr_bytes_read)
{
    size_t written = 0, offset = 0;

    while (offset < in_size && written + 1 < out_max_size)
    {
        uint8_t b = in[offset++];

        out[written++]  = val2hexc(b >> 4);
        out[written++]  = val2hexc(b & 0x0f);
    }

    if (ptr_bytes_written)
        *ptr_bytes_written = written;

    if (ptr_bytes_read)
        *ptr_bytes_read = offset;
}

static
size_t base64decode (uint8_t in[4], uint8_t out[3])
{
    uint8_t i0, i1, i2, i3;

    if (in[0] == '=' || in[1] == '=')
        return 0;   // error
    if (in[2] == '=' && in[3] != '=')
        return 0;   // error

    i0 = base64c2val (in[0]);
    i1 = base64c2val (in[1]);
    i2 = base64c2val (in[2]);
    i3 = base64c2val (in[3]);

    if (i0 == 0xFF || i1 == 0xFF || i2 == 0xFF || i3 == 0xFF)
        return 0;   // error

    out[0] = (i0 << 2) | (i1 >> 4);
    out[1] = ((i1 & 0x0F) << 4) | (i2 >> 2);
    out[2] = ((i2 & 0x03) << 6) | i3;

    return 3 - (in[2] == '=') - (in[3] == '=');
}

void base642bin (const char *in, size_t in_size, uint8_t *out, size_t out_max_size,
    size_t *ptr_bytes_written, size_t *ptr_bytes_read)
{
    size_t offset = 0, written = 0;

    while (offset + 2 < in_size)
    {
        uint8_t inc[4], outc[3];

        // read four characters
        for (size_t k = 0; k < 4; k++)
            inc[k] = in[offset + k];
        offset  += 4;

        size_t cnt = base64decode (inc, outc);

        for (size_t k = 0; k < cnt; k++)
            *out++ = outc[k];

        written += cnt;
        if (cnt != 3)
            break ;
    }

    if (ptr_bytes_read)
        *ptr_bytes_read = offset;

    if (ptr_bytes_written)
        *ptr_bytes_written = written;
}

void bin2base64 (
    const uint8_t *in, size_t in_size, char *out, size_t out_max_size,
    size_t *ptr_bytes_written, size_t *ptr_bytes_read)
{
    size_t offset = 0, written = 0;

    while (offset < in_size && written + 3 < out_max_size)
    {
        written += 4;

        // read a three byte sequence, fill with zeros
        uint8_t c0 = in[offset++];
        *out++ = val2base64c (c0 >> 2);

        if (offset >= in_size)
        {
            *out++ = val2base64c ((c0 & 0x03) << 4);
            *out++ = '=';
            *out++ = '=';
            break ;
        }

        uint8_t c1 = in[offset++];
        *out++ = val2base64c (((c0 & 0x03) << 4) + (c1 >> 4));

        if (offset >= in_size)
        {
            *out++ = val2base64c ((c1 & 0x0F) << 2);
            *out++ = '=';
            break ;
        }

        uint8_t c2 = in[offset++];
        *out++ = val2base64c (((c1 & 0x0F) << 2) + (c2 >> 6));
        *out++ = val2base64c (c2 & 0x3F);
    }

    if (ptr_bytes_written)
        *ptr_bytes_written = written;
    if (ptr_bytes_read)
        *ptr_bytes_read = offset;
}
