#include <stdio.h>
#include <stdlib.h>


//  converts a hexadecimal representation into a binary representation
uint8_t* hex_to_bin (char* hex_string, size_t size);

// converts a binary representation into a hexadecimal representation
char* bin_to_hex (uint8_t* bin_string, size_t size);


//  converts a base64 representation into a binary representation
uint8_t* base64_to_bin (char* base64_string, size_t size);

// converts a binary representation into a base64 representation
char* bin_to_base64 (uint8_t* bin_string, size_t size);

// takes a char with values 0 - 9 and A - F, and outputs its numerical value
uint8_t value_from_hex (char x);

// takes 4 bits (a number 0 - 15) and outputs its hex representation
char hex_from_value (uint8_t x);

// takes a char with values A - Z, a - z, 0 - 9 and +, / and outputs its corresponding
// numerical value
uint8_t value_from_base64 (char x);

// takes 6 bits and outputs the corresponding base64 character
char base64_from_value (uint8_t x);


// bitwise xor of strings of same length
uint8_t* xor_ (uint8_t* string1, uint8_t* string2, size_t size);

// bitwise xor with one fixed byte
uint8_t* xor_const (uint8_t* string, uint8_t x, size_t size);

// prints hex-representation of a number
void print_hex (char* hex_string, size_t size);

// prints base64-representation of a number
void print_base64 (char* base64_string, size_t size);

// prints bin-representation of a number
void print_bin (uint8_t* bin_string, size_t size);







/*
 *  hex <-> bin
 */

uint8_t* hex_to_bin (char* hex_string, size_t size)
{
    uint8_t* bin_string;
    /*
     * size is divisible by 2 as hex is saved in pairs of chars
     */
    size_t nsize = size / 2;
    bin_string = (uint8_t*) malloc(nsize);
    if (bin_string == NULL)
    {
        fprintf(stderr, "Memory Allocation Error\n");
        return NULL;
    }

    for (size_t i = 0; i < nsize; i++)
    {
        uint8_t v = value_from_hex(hex_string[2*i]);
        if (v != 0xFF)
        {
            bin_string[i] = (v << 4);
        }
        else
        {
            fprintf(stderr, "Input failure\n");
            return NULL;
        }

        v = value_from_hex(hex_string[2*i + 1]);
        if (v != 0xFF)
        {
            bin_string[i] += v;
        }
        else
        {
            fprintf(stderr, "Input failure\n");
            return NULL;
        }
    }

    return bin_string;
}

char* bin_to_hex (uint8_t* bin_string, size_t size)
{
    char* hex_string;
    hex_string = (char*) malloc (2 * size);
    if (hex_string == NULL)
    {
        fprintf(stderr, "Memory Allocation Error\n");
        return NULL;
    }

    for (size_t i = 0; i < size; i++)
    {
        char x = hex_from_value(bin_string[i] & 0x0F);
        if (x != 0)
        {
            hex_string[2*i] = x;
        }
        else
        {
            fprintf(stderr, "Input failure\n");
            return NULL;
        }

        x = hex_from_value(bin_string[i] >> 4);
        if (x != 0)
        {
            hex_string[2*i + 1] = x;
        }
        else
        {
            fprintf(stderr, "Input failure!\n");
            return NULL;
        }
    }

    return hex_string;
}

uint8_t value_from_hex (char x)
{
    if (x >= '0' && x <= '9')
        return (uint8_t) x - '0';
    if (x >= 'A' && x <= 'F')
        return (uint8_t) x - 'A' + 10;
    if (x >= 'a' && x <= 'f')
        return (uint8_t) x - 'a' + 10;
    return 0xFF;
}

char hex_from_value (uint8_t x)
{
    if (x < 10)
        return (char) (x + '0');
    if (x < 16)
        return (char) (x + 'A' - 10);
    return 0;
}


/*
 *  base64 <-> bin
 */

/*
 *  a base64 number will always be saved in 4-tuples
 *  this helps the conversion to binary, as then any 4-tuple
 *  corresponds to a triple of binary numbers and vice versa
 *
 */

uint8_t* base64_to_bin (char* base64_string, size_t size)
{
    uint8_t* bin_string;
    size_t bin_size = 3 * (size / 4);
    bin_string = (uint8_t*) malloc (bin_size);
    if (bin_string == NULL)
    {
        fprintf(stderr, "Memory Allocation Error\n");
        return NULL;
    }

    for (size_t i = 0; i < bin_size / 3; i++)
    {
        uint8_t v = value_from_base64 (base64_string[4*i]);
        if (v == (1 << 7))
            return NULL;
        if (v == (1 << 6))
        {
            fprintf(stderr, "Input failure\n");
            return NULL;        // '=' should only appear in indexes congruent 1 or 2 mod 3
        }
        bin_string[3*i] = v << 2;

        v = value_from_base64 (base64_string[4*i + 1]);
        if (v == (1 << 7))
            return NULL;
        if (v == (1 << 6))
        {
            bin_size -= 2;
            break;
        }
        bin_string[3*i] += v >> 4;
        bin_string[3*i + 1] = v << 4;

        v = value_from_base64 (base64_string[4*i + 2]);
        if (v == (1 << 7))
            return NULL;
        if (v == (1 << 6))
        {
            bin_size -= 1;
            break;
        }
        bin_string[3*i + 1] += v >> 2;
        bin_string[3*i + 2] = v << 6;

        v = value_from_base64 (base64_string[4*i + 3]);
        if (v == (1<<7))
            return NULL;
        bin_string[3*i + 2] += v;
    }
    return bin_string;
}


char* bin_to_base64 (uint8_t* bin_string, size_t size)
{
    char* base64_string;

    if (size % 3 == 0)
        base64_string = (char*) malloc(4 * size / 3);

    base64_string = (char*) malloc(4 * (size / 3 + 1));
    if (base64_string == NULL)
    {
        fprintf(stderr, "Memory Allocation Error\n");
        return NULL;
    }

    for (size_t i = 0; i < size/3; i++)
    {
        char v = base64_from_value (bin_string[3*i] >> 2);
        if(v == '\n')
        {
            return NULL;
        }
        base64_string[4*i] = v;

        v = base64_from_value( ((bin_string[3*i] & 0x03) << 4) + (bin_string[3*i + 1] >> 4) );
        if(v == '\n')
        {
            return NULL;
        }
        base64_string[4*i + 1] = v;

        v = base64_from_value( ((bin_string[3*i + 1] & 0x0F) << 2) + (bin_string[3*i + 2] >> 6));
        if(v == '\n')
        {
            return NULL;
        }
        base64_string[4*i + 2] = v;

        v = base64_from_value(bin_string[3*i + 2] & 0x3F); //0x3F = (00111111)_2
        if(v == '\n')
        {
            return NULL;
        }
        base64_string[4*i + 3] = v;
    }

    if(size % 3 == 1)
    {
        char v = base64_from_value (bin_string[size - 1] >> 2);
        if(v == '\n')
        {
            return NULL;
        }
        base64_string[4*(size/3)] = v;

        v = base64_from_value ((bin_string[size - 1]  & 0x03) << 4);
        if(v == '\n')
        {
            return NULL;
        }
        base64_string[4*(size/3) + 1] = v;

        base64_string[4*(size/3) + 2] = '=';
        base64_string[4*(size/3) + 3] = '=';
    }

    if(size % 3 == 2)
    {
        char v = base64_from_value (bin_string[size - 2] >> 2);
        if(v == '\n')
        {
            return NULL;
        }
        base64_string[4*(size/3)] = v;

        v = base64_from_value ( ((bin_string[size - 2]  & 0x03) << 4) + (bin_string[size - 1] >> 4));
        if(v == '\n')
        {
            return NULL;
        }
        base64_string[4*(size/3) + 1] = v;

        v = base64_from_value( (bin_string[size - 2] & 0x0F) << 2);
        if(v == '\n')
        {
            return NULL;
        }
        base64_string[4*(size/3) + 2] = v;

        base64_string[4*(size/3) + 3] = '=';
    }

    return base64_string;
}



uint8_t value_from_base64 (char x)
{
    /*
     *  A - Z for 0 to 26
     *  a - z for 27 to 51
     *  0 - 9 for 52 to 61
     *  + for 62, / for 63
     */
    if (x >= 'A' && x <= 'Z')
        return x - 'A';
    if (x >= 'a' && x <= 'z')
        return x - 'a' + 26;
    if (x >= '0' && x <= '9')
        return x - '0' + 52;
    if (x == '+')
        return 62;
    if (x == '/')
        return 63;
    if (x == '=')               // padding exception
        return 1 << 6;
    fprintf(stderr, "Input Failure\n");
    return 1 << 7;
}

char base64_from_value (uint8_t x)
{
    if (x <= 25)
        return x + 'A';
    if (x <= 51)
        return x + 'a' - 26;
    if (x <= 61)
        return x - 52 + '0';
    if (x == 62)
        return '+';
    if (x == 63)
        return '/';
    fprintf(stderr, "Input Failure\n");
    return '\n';
}


/*
 *  xor-function: takes two byte-streams of same length
 *  and returns their bitwise xor
 */

uint8_t* xor_ (uint8_t* string1, uint8_t* string2, size_t size)
{
    uint8_t* out;
    out = (uint8_t*) malloc(size);
    if (out == NULL)
    {
        fprintf(stderr, "Memory Allocation Error\n");
        return NULL;
    }

    for (size_t i = 0; i < size; i++)
    {
        out[i] = string1[i] ^ string2[i];
    }
    return out;
}

/*
 *  xor's a byte-stream with the constant stream x
 */

uint8_t* xor_const (uint8_t* string, uint8_t x, size_t size)
{
    uint8_t* out;
    out = (uint8_t*) malloc(size);
    if (out == NULL)
    {
        fprintf(stderr, "Memory Allocation Error\n");
        return NULL;
    }

    for (size_t i = 0; i < size; i++)
    {
        out[i] = string[i] ^ x;
    }
    return out;
}

/*
 *  text to binary in utf8 and vice versa
 */




/*
 *  print functions
 */

void print_bin (uint8_t* bin_string, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        uint8_t temp = bin_string[i];
        for (int j = 0; j < 8; j++)
        {
            if ( ((temp >> (7 - j)) & 1) == 1)
                printf("1");
            else
                printf("0");
        }

        if (i % 8 == 7)
            printf("\n");
        else
            printf(" ");
    }
    printf("\n");
}

void print_hex (char* hex_string, size_t size)
{
    if (size % 2 != 0)
    {
        fprintf(stderr, "Incorrect hexadecimal representation\n");
        return;
    }
    size_t nsize = size / 2;
    for (size_t i = 0; i < nsize; i++)
    {
        printf("%c%c ", hex_string[2*i + 1], hex_string[2*i]);
    }
    printf("\n");
}

void print_base64 (char* base64_string, size_t size)
{
    for (size_t i = 0; i < size / 4; i++)
    {
        printf("%c%c%c%c ", base64_string[4*i], base64_string[4*i + 1],
            base64_string[4*i + 2], base64_string[4*i + 3]);
    }
    printf("\n");
}


void print_string (uint8_t* string, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (string[i] >= 128)
        {
            fprintf(stderr, "Input Failure. This is not a string of characters.\n");
            return;
        }
        putchar(string[i]);
    }
    putchar('\n');
}





