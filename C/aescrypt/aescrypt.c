#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#include "binrep.h"
#include "aes128.h"

bool load_key (uint32_t *key, const char *str, bool hexkey)
{
    int length = strlen (str);

    uint8_t key_decoded[16];

    const uint8_t *data = NULL;

    if (hexkey)
    {
        if (length != 32)
        {
            fprintf (stderr, "Invalid key length.");
            return false;
        }

        size_t bytes_written;

        hex2bin (str, 32, key_decoded, 16, &bytes_written, NULL);

        if (bytes_written != 16)
        {
            fprintf (stderr, "Malformed key.");
            return false;
        }

        data = key_decoded;
    }
    else
    {
        if (length != 16)
        {
            fprintf (stderr, "Invalid key length.");
            return false;
        }

        data = (uint8_t*) str;
    }

    aes128_load_block (key, data);
    return true;
}

void pkcs7_pad(uint8_t *data, size_t have, size_t want)
{
    uint8_t pad = (want - have) & 0xff;

    while (have < want)
        data[have++] = pad;
}

void cbc_xor (uint32_t *data, uint32_t *v)
{
    for (int k = 0; k < 4; k++)
        data[k] ^= v[k];
}


/* TODO:
 *  AES Encrypter/Decrypter
 *
 *  aescrypt [-d] -m cbc|ecb [-i file.input]
 *      -d  decrypt instead of encrypt
 *      -m  mode: cbc or ecb
 *      -k  key in hexadecimal representation
 *      -s  key in ascii representation
 *      -i  input file, default is stdin
 *      -o  output file, default is stdout
 */

/*
 *
 *  aescrypt [-d] -s filename
 *  Prints hex dump of cbc encrypted data.
 */

void print_help ()
{
    puts ("aescrypt [-d] [-h] -s \"KEY\" file");
    puts ("read file and prints hex dump to stdout after encryption with aes128");
    puts ("-d\tdecrypt instead of encrypt");
    puts ("-h\tkey in hexadecimal representation");
    puts ("-s\tkey");
    puts ("-i\thexadecimal representation of initialisation vector, if provided\n\tcbc is used");
    puts ("file\tfile to be read, if no file set stdin is used");

}



static
void print_block (uint32_t *block)
{
    uint8_t *_block = (uint8_t *) block;

    for (int i = 0; i < 16; i++)
    {
        printf ("%02x", _block[i]);
    }
    putchar ('\n');
}

static
void print_block_ascii (uint32_t *block)
{
    uint8_t *_block = (uint8_t *) block;

    for (int i = 0; i < 16; i++)
    {
        printf ("%c", _block[i]);
    }
    putchar ('\n');
}


void print_word (uint32_t w)
{
    printf("%02x", (w >> 24) & 0xff);
    printf("%02x", (w >> 16) & 0xff);
    printf("%02x", (w >> 8) & 0xff);
    printf("%02x", (w >> 0) & 0xff);

    printf("\n");
}


int main (int argc, char *argv[])
{
    bool decrypt = false, hexkey = false;

    char *filename = NULL, *keystring = NULL, *ivstring = NULL;

    if (argc == 1)
    {
        print_help();
        return EXIT_SUCCESS;
    }

    // parse options
    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];

        if (arg[0] == '-')
        {
            switch (arg[1])
            {
                case 'd':
                    decrypt = true;
                    break;

                case 'h':
                    hexkey = true;
                    break ;

                case 'i':
                    if (arg[2] != '\0')
                        ivstring = arg + 2;
                    else
                        ivstring = (i + 1 < argc) ? argv[++i] : NULL;

                    break ;

                case 's':
                    if (arg[2] != '\0')
                        keystring = arg + 2;
                    else
                        keystring = (i + 1 < argc) ? argv[++i] : NULL;

                    break ;
            }
        }
        else
        {
            filename = arg;
        }
    }

    // load the key
    if (!keystring)
    {
        fprintf(stderr, "No key specified.\n");
        return EXIT_FAILURE;
    }

    uint32_t key[4];
    if(!load_key (key, keystring, hexkey))
        return EXIT_FAILURE;

    uint32_t w[4*11];
    aes128_key_expand (key, w);

    uint32_t iv[4];

    bool cbc = (ivstring != NULL);

    if (cbc)
    {
        if(!load_key (iv, ivstring, true))
            return EXIT_FAILURE;
    }

    // open file
    FILE *infile;

    if (filename)
    {
        infile = fopen (filename, "r");
        if (!infile)
        {
            fprintf(stderr, "Could not open file '%s': %s\n", filename, strerror (errno));
        }
    }
    else
    {
        infile = stdin;
    }



    if (decrypt)
    {
        char data [32];
        uint32_t block[4], chiff[4];

        while (!feof (infile))
        {
            size_t read = fread (data, sizeof(char), 32, infile);

            if (read == 0)
                break ;

            if (read != 32)
            {
                fprintf(stderr, "Input file corrupted. Could not read 32 byte, only %lu.\n", read);
                return EXIT_FAILURE;
            }

            uint8_t bin[16];
            size_t bytes_written;
            hex2bin (data, 32, bin, 16, &bytes_written, NULL);

            if (bytes_written != 16)
            {
                fprintf(stderr, "Input file corrupted. Invalid hexcode.\n");
                return EXIT_FAILURE;
            }

            char out[16+1];


            aes128_load_block (chiff, bin);
            aes128_block_decrypt (chiff, w, block);

            if (cbc) {
                cbc_xor (block, iv);
                memcpy (iv, chiff, sizeof(iv));
            }

            aes128_write_block ((uint8_t*) out, block);
            out[16] = '\0';

            printf ("%s", out);
        }
    }
    else
    {
        uint8_t data [16];

        while (!feof (infile))
        {
            size_t read = fread (data, sizeof(uint8_t), 16, infile);

            pkcs7_pad(data, read, 16);

            char hex[32 + 1];
            uint32_t block[4], chiff[4];

            aes128_load_block (block, data);

            if (cbc)
                cbc_xor (block, iv);

            aes128_block_encrypt (block, w, chiff);

            if (cbc)
                memcpy (iv, chiff, sizeof(iv));

            aes128_write_block (data, chiff);

            bin2hex (data, 16, hex, 32, NULL, NULL);
            hex[32] = '\0';

            printf ("%s", hex);
        }
    }

    return EXIT_SUCCESS;
}

