#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "functions.h"




int main (int argc, char *argv[])
{

    char **input = NULL;                //array of strings
    int i;
    int comp;

    i = get_array_string(&input);
    if (i == -1)
    {
        printf("ERROR!\n");
        return 1;
    }

    print_string_array(input);
    printf("%d\n",i);
    printf("%lx, %lx\n", (unsigned long int) input[0], (unsigned long int) input[1]);

    comp = compare_two_strings(input[0], input[1]);


    if(comp == -1)
    {
        printf("The first string is \"bigger\"\n");
        printl(input[0]);
    } else {
        if(comp == 1)
        {
            printf("The second string is \"bigger\"\n");
        } else {
            printf("The strings coincide\n");
        }
        printl(input[1]);
    }


            //print_string_array(input);

    free(input);


    return 0;
}

