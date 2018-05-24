#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "binrep.h"
#include "binmanip.h"
#include "file-utils.h"

// make sure this is a multiple of 4 and 3
#define BUFFER_SIZE 128 * 4 * 3

#define LINE_BREAK_DISTANCE     64
#define SPACE_DISTANCE          16

void print_help ()
{
    puts ("xorcrypt [-d] [-h] [-o outfile] key infile");
    puts ("Encrypts/decrypts a file with a xor chiffre. Outputs the data base64 encoded.");
    puts ("-d decrypt instead of encrypt");
    puts ("-h specify key as hexadecimal string");
    puts ("-o specify output file");
    puts ("-p pretty prints the output");
}

int main (int argc, char *argv[])
{
    bool decrypt = false, hexkey = false, pretty = false;
    char *key_string = NULL, *filename = NULL, *out_filename = NULL;

    if (argc == 1)
    {
        print_help ();
        return EXIT_SUCCESS;
    }

    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];

        if (arg[0] == '-')
        {
            switch (arg[1])
            {
                case 'h':
                    hexkey = true;
                    break;
                case 'd':
                    decrypt = true;
                    break;
                case 'p':
                    pretty = true;
                    break;
                case 'o':
                    if (arg[2] == '\0')
                    {
                        if (i + 1 < argc)
                        {
                            out_filename = argv[++i];
                        }
                        else
                        {
                            fprintf(stderr, "Missing output filename.\n");
                            return EXIT_FAILURE;
                        }
                    }
                    else
                    {
                        out_filename = arg + 2;
                    }
                    break;

                default:
                    fprintf(stderr, "Unknown switch: %c. Ignored.\n", arg[1]);
            }
        }
        else
        {
            if (!key_string) {
                key_string = arg;
            } else if (!filename) {
                filename = arg;
            } else {
                fprintf(stderr, "Too many arguments. Ignoring '%s'.\n", arg);
                break;
            }
        }
    }

    if (decrypt && pretty)
    {
        fprintf(stderr, "Pretty flag in decrypt mode ignored.\n");
    }

    if (!key_string || !filename)
    {
        fprintf(stderr, "Missing parameters. Terminate.\n");
        return EXIT_FAILURE;
    }

    size_t key_string_length = strlen (key_string);

    if (hexkey && (key_string_length & 0x01))
    {
        fprintf(stderr, "Invalid key length.\n");
        return EXIT_FAILURE;
    }

    size_t key_length = hexkey ? key_string_length / 2 : key_string_length;

    uint8_t key[key_length];

    // decode the key if necessary
    if (hexkey)
    {
        size_t written;
        hex2bin (key_string, key_string_length, key, key_length, &written, NULL);

        if (written != key_length)
        {
            fprintf(stderr, "Invalid key representation.\n");
            return EXIT_FAILURE;
        }
    }
    else
    {
        memcpy (key, key_string, key_length);
    }


    // open the input file and
    FILE* in_file = fopen (filename, decrypt ? "r" : "rb");
    if (!in_file)
    {
        fprintf(stderr, "Could not open file '%s': %s\n", filename, strerror (errno));
        return EXIT_FAILURE;
    }

    FILE* out_file;
    if (out_filename)
    {
        out_file = fopen (out_filename, decrypt ? "wb" : "w");
        if (!out_file)
        {
            fprintf(stderr, "Could not open file '%s': %s\n", out_filename, strerror (errno));
            fclose (in_file);
            return EXIT_FAILURE;
        }
    }
    else
    {
        out_file = stdout;
    }


    // switch on decoding or encoding
    if (decrypt)
    {
        char base64_buffer [BUFFER_SIZE];
        uint8_t binary_buffer [BUFFER_SIZE];

        size_t key_offset = 0;

        while (!feof(in_file))
        {
            size_t written, read;

            read = fread_buffer_ignore_space (base64_buffer, BUFFER_SIZE, in_file);

            if(!base642bin (base64_buffer, read, binary_buffer, BUFFER_SIZE, &written, NULL))
            {
                fprintf(stderr, "Corrupted input file. Invalid base64 enconding.\n");
                break;
            }

            xorbro (binary_buffer, written, key, key_length, key_offset);
            fwrite (binary_buffer, sizeof(char), written, out_file);

            key_offset = (key_offset + written) % key_length;
        }
    }
    else
    {
        // estimate the base64 buffer size
        size_t base64_buffer_size = 4 * ( BUFFER_SIZE + 1) / 3;

        uint8_t binary_buffer[BUFFER_SIZE];
        char base64_buffer[base64_buffer_size];

        size_t key_offset = 0, write_offset = 0;


        while (!feof(in_file))
        {
            size_t written, read = fread (binary_buffer, sizeof(uint8_t), BUFFER_SIZE, in_file);

            xorbro (binary_buffer, read, key, key_length, key_offset);
            bin2base64 (binary_buffer, read, base64_buffer, base64_buffer_size, &written, NULL);

            for (int k = 0; k < written; k++)
            {
                fputc (base64_buffer[k], out_file);
                write_offset++;

                if (pretty) {
                    if (write_offset % LINE_BREAK_DISTANCE == 0)
                        fputc ('\n', out_file);
                    else if (write_offset % SPACE_DISTANCE == 0)
                        fputc ('\x20', out_file);
                }
            }

            key_offset = (key_offset + read) % key_length;
        }

        if (pretty && write_offset % LINE_BREAK_DISTANCE != 0)
            fputc ('\n', out_file);
    }

    if (out_filename)
        fclose (out_file);
    fclose (in_file);
}
