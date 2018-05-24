#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void make_zero (int *c, int d)
{
    for (int i = 0; i < d; i++)
    {
        c[i] = 0;
    }
}

void pol_mult (int *p, int *ar1, int *ar2, int d)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            p[i+j] = (p[i+j] + ar1[i] * ar2[j]) & 2;
        }
    }
}

int pol_comp (int *ar1, int *ar2, int d)    // returns 0 if input pol's
{                                           // coincide and 1 otherwise
    for (int i = 0; i < d; i++)
    {
        if (ar1[i] != ar2[i])
            return 0;
    }
    return 1;
}

// sets pol s depending on i < 2^d
void set (int *s, int d, int k)
{
    for (int i = 0; i < d; i++)
    {
        if ((k >> i) & 1)
        {
            s[i] = 1;
//            printf("%d\n", s[i]);
            continue;
        }
        s[i] = 0;
//        printf("%d\n", s[i]);
    }
}

int compare (int *c, int *ar1, int *ar2, int d)
{
    int *x;
    int t;

    x = malloc (2*d);
    if (x == NULL)
    {
        printf("FAIL!\n");
        return -1;
    }

    make_zero (x, 2*d);
    pol_mult (x, ar1, ar2, d);

    t = pol_comp (c, x, d);
    free (x);

    return t;
}


int factorize (int *c, int *ar1, int *ar2, int d)
{
    int d_sq = pow(2, d);
    int t = -1;

    for (int i = 0; i < d_sq; i++)
    {
        for (int j = 0; j < d_sq; j++)
        {
            set (ar1, d, i);
            set (ar2, d, j);
            t = compare (c, ar1, ar2, d);
            if (t || t == -1)
                return t;
        }
    }
    return 0;
}


void print_pol (int *s, int d)
{
    for (int i = d - 1; i > 0; i--)
    {
        if (s[i])
        {
            printf("x^%d + ", i);
        }
    }
    if (s[0])
        printf("%d ", 1);
}


void print_factorization (int *c, int *ar1, int *ar2, int d, int t)
{

    if (t == -1)
    {
        printf("FAIL!\n");
        return;
    }
    if (t == 0)
    {
        printf("The polynomial \t");
        print_pol (c, d);
        printf("\t is irreducible!\n");
        return;
    }

    print_pol (c, 2*d);
    printf("\t = (");
    print_pol (ar1, d);
    printf(") (");
    print_pol (ar2, d);
    printf(")\n");
    return;
}


int main (int argc, char *argv[])
{
    int *s1, *s2;   // the pol's to run through
    int *comp;      // the pol to factorize

    int d = 9;
//    int d_sq = pow(2, d);
    int test = 1;

    comp = malloc (d);
    if (comp == NULL)
    {
        printf("FAIL\n");
        return 0;
    }
    s1 = malloc (d);
    if (s1 == NULL)
    {
        printf("FAIL\n");
        return 0;
    }
    s2 = malloc (d);
    if (s2 == NULL)
    {
        printf("FAIL\n");
        return 0;
    }

    make_zero (s1, d);
    make_zero (s2, d);

    make_zero (comp, 2*d);
    comp[0] = 1;
    comp[1] = 1;
    comp[2] = 1;
    comp[4] = 1;
    comp[8] = 1;

    print_pol (comp, d);
    // returns 1 if comp can be factored
    // s1 and s2 are then changed into the factors of comp
    // if comp is irreducible, test will be set to 0
    test = factorize (comp, s1, s2, d);

    print_factorization (comp, s1, s2, d, test);

    free(comp);
    free(s1);
    free(s2);

    return 0;
}













