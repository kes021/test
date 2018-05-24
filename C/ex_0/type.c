#include <stdio.h>


int main (int argc, char *argv[])
{
    unsigned int c = 0x80000000 - 1;
    int d = 1324155;

    short e = d;

    printf ("%d \n", e);

    return 0;
}
