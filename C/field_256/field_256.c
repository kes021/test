#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

uint16_t mult (uint16_t a, uint16_t b)
{
    uint16_t x = 0;

    while (a != 0)
    {
        if(a & 1)
        {
            x ^= b;
        }

        a = a >> 1;
        b = b << 1;
    }
    return x;
}

int deg (uint16_t a)
{
    int i = 0;
    while (a != 0)
    {
        a = a >> 1;
        i++;
    }
    return i-1;
}


void divmod (uint16_t a, uint16_t b, uint16_t *x, uint16_t *y)      // a = *x * b + *y
{
    *x = 0;
    if (b == 0)
    {
        *y = a;
        return;
    }

    int i, j;
    j = deg (a);
    i = deg (b);

    b = b << (j - i);

    while (j >= i)
    {
        *x = *x << 1;
        if (a == b)
        {
            *x = *x << j;
            *x |= 0x01;
            a = 0;
            break;
        }
        if (a & (1 << j))
        {
            *x |= 0x01;
            a ^= b;
        }

        b = b >> 1;
        j--;
    }
    *y = a;
}

uint16_t div (uint16_t a, uint16_t b)
{
    uint16_t x, y;
    divmod (a, b, &x, &y);
    return x;
}

uint16_t mod (uint16_t a, uint16_t b)
{
    uint16_t x, y;
    divmod (a, b, &x, &y);
    return y;
}


void print_pol (uint16_t a)
{
    int i = 1;

    if (a == 0)
    {
        printf ("0");
        return;
    }

    for (int k = 15; k > 1; k--)
    {

        if (a & (1 << k))
        {
            if (i == 0)
            {
                printf(" + ");
            }
            i = 0;
            printf("x^%d", k);
        }
    }



    if (a & (1 << 1))
    {
        if (i == 0)
        {
            printf(" + ");
        }
        i = 0;
        printf("x");
    }


    if (a & 1)
    {
        if (i == 0)
        {
            printf(" + ");
        }
        printf("1");
    }
}

bool check_irred (uint16_t a)
{

    for (uint16_t b = 2; b < a; b++)
    {
        if (mod (a,b) == 0)
        {
            //printf("hohoho");
            return false;
        }
    }
    return true;
}

void find_irreds ()
{
    for (uint16_t a = 2; a < 512; a++)
    {
        if (check_irred(a))
        {
            //printf ("The polynomial \n");
            print_pol(a);
            //printf("is irreducible");
        }
    }
}

uint16_t set_field ()
{
    for (uint16_t a = 2; a < 512; a++)
    {
        if (check_irred(a))
        {
            if (deg(a) == 8)
                return a;
        }
    }
    return 0;
}

/*uint16_t power (int x, uint16_t a)
{
    if (x == 0)
        return 1;
    if (x == 1)
        return a;
    if (!(x & 1))
        return power (x/2, mult (a,a));
    return mult(a,power (x/2, mult(a,a)));
}*/

uint16_t mult_x (uint16_t a, uint16_t b, uint16_t x)
{
    return mod (mult(a,b),x);
}



bool check_gen (uint16_t a, uint16_t x) // checks if given nonzero polynomial a is a generator of F_256^*
{
    uint16_t b = 1;
    for (int i = 1; i < 255; i++)
    {
        b = mult_x (a,b,x);
        if (1 == b)
            return false;
    }
    return true;
}


uint16_t find_gens (uint16_t x)
{
//    printf("The following is a complete list of generators of F_256 \n");
//    printf("defined using the irreducible polynomial ");
//    print_pol(x);

    uint16_t y = 0; //set smallest generator

    for (uint16_t a = 2; a < 256; a++)
    {
        if (check_gen(a,x))
        {
//            print_pol (a);
            if (y == 0)
                y = a;
        }
    }
    return y;
}


void make_table (uint16_t x, uint16_t y, uint16_t *exp, int *log)
{
    uint16_t a = 1;

    for (int i = 0; i < 255; i++)
    {
        exp[i] = a;
        log[a] = i;
        a = mult_x(a,y,x);
//        print_pol(a);
    }
    log[0] = 0;
    printf("%d\n", log[0]);
    printf("%d\n", log[1]);
}


void print_exp_table (uint16_t *table)
{
    for (int i = 0; i < 255; i++)
    {
        printf ("exp(%d) =\t", i);
        print_pol (table[i]);
        printf("\n");
    }
}

void print_log_table (int *table)
{
    for (uint16_t i = 0; i < 255; i++)
    {
        printf("%3.1d \t=\t log (", table[i]);
        print_pol (i);
        printf(")\n");
    }
}


uint16_t fastmult (uint16_t a, uint16_t b, uint16_t *exp, int *log)
{
    if (log[a] + log[b] == 255)
        return 1;
    if (a == 0 || b == 0)
        return 0;

    return exp[log[a] + log[b]];
}

uint16_t fastinvert (uint16_t a, uint16_t *exp, int *log)
{
    if (a == 0)
        return 0;
    return exp[255 - log[a]];
}



int main (int argc, char *argv[])
{
/*
    for (uint16_t i = 0; i < 16; i++)
        print_pol(i);
*/

/*
    for (uint16_t j = 0; j < 16; j++)
    {
        printf ("\n %d \n", j);
        print_pol(j);
        printf("\n");
        for (uint16_t k = 0; k < 16; k++)
        {
            print_pol(mult(j,k));
        }
    }
*/      // f = mg + r

/*
    for (uint16_t j = 1; j < 4; j++)
    {
        for (uint16_t k = 1; k < 4; k++)
        {
            printf("k is: ");
            print_pol (k);

            printf("j is: ");
            print_pol (j);

            printf("k/j is: ");
            print_pol (div (k, j));

            printf("k mod j is: ");
            print_pol (mod (k, j));

            print_pol (mult (div (k,j), j) ^ mod (k,j));
            printf("\n");
        }
    }
*/
//    find_irreds();

    uint16_t x, y;
    x = set_field();

    uint16_t exp[255];
    int log[255];

    //print_pol(x);

    y = find_gens(x);

    printf("\n");
    printf("The smallest generator of the multiplicative group is \n");
    print_pol(y);
    printf("\n");

    make_table(x, y, exp, log);
    print_exp_table (exp);
    print_log_table (log);

    print_pol(fastmult(y, fastinvert(y, exp, log), exp, log));
    printf("\n");
    print_pol(fastinvert(y,exp,log));
    printf("\n");
    print_pol(fastmult(y, 0, exp, log));
    printf("\n");
    print_pol(fastmult(0, y, exp, log));
    printf("\n");

    return 0;
}
