#include <stdio.h>

int square (int x)
{
    return x*x;
}

int power (int number, int exponent)
{
    if (exponent == 0)
        return 1;
    if (exponent == 1)
        return number;
    if ((exponent & 1) == 0)
        return power (square(number), exponent/2);
    return number * power (square(number), (exponent - 1)/2);
}

void print_decomposition (int y, int x, int j, int j2, int k, int k2)
{
    printf ("10^%d = %d can be decomposed as %d^2 + %d^2\n", x,y,j,k);
    printf ("That is, %d = %d + %d\n", y, j2, k2);
    return;
}

void decompose (int x)
{
    int y = power (10,x);
    int sqj, sqk;

    for (int j = 1; j < y; j++)
    {
        for (int k =0; k < y; k++)
        {
            sqj = square (j);
            sqk = square (k);
            if (y == sqj + sqk)
            {
                print_decomposition (y, x, j, sqj, k, sqk);
                return;
            }
        }
    }
    printf ("%d is not a sum of two squares\n", y);
}


int main (int argc, char *argv[])
{

    for (int i = 1; i < 9; i++)
    {
        decompose(i);
    }

    return 0;
}
