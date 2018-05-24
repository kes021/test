#include <stdio.h>


int main ()
{
    printf ("Hello World!\n");

    printf ("My name is Alpay\n");

    int x;
    x = 7;
    printf ("%d \n", x);

    int y;
    y=2;
    printf("%d \n", y);

    printf ("%d \n", x + y);
    printf("%d\n", y*x);
    printf("%d\n", x / y);
    printf("%d\n", x % y);

    int i = 1;
    int sum = 0;

    while (i < 10)
    {
        sum = sum + i;
        i = i + 1;
    }

    printf ("%d \n", sum);

    return 0;
}
