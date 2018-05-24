#include <stdlib.h>
#include <stdio.h>

#include "functions.h"


int getl (char **string)                //gets string pointer (adress of some string)
{                                       //and saves the given string into the memory
    int i = -1;                         //the pointer has saved
    int j;
    char c = '\0';
    char *temp = NULL;

    *string = NULL;

    while(1)                            //the termination condition will be given in
    {                                   //the loop

        ++i;
        temp = realloc(*string, 32 * (i+1) * sizeof(char));
        if (temp == NULL)               //allocates space for the string and reallocates
        {                               //if allocated space was insufficient
            printf("Memory allocation failed\n");   //then it tests, whether allocation
            free(*string);                          //has been successful
            return -1;
        }
        *string = temp;

        for(j = 0; j < 32; ++j)         //gets the next 32 char's, unless it finds a
        {                               //new line character, then it stops and finishes
            c = getchar();              //with a new line and a '\0' character
            if (c == '\n')
            {
                (*string)[32 * i + j] = '\n';
                if (j == 31)
                {
                    temp = realloc(*string, 32 * (i+1) * sizeof(char) + 1);
                    if (temp == NULL)
                    {
                        printf("Memory allocation failed\n");
                        free(*string);
                        return -1;
                    }
                    *string = temp;
                }
                (*string)[32 * i + j + 1] = '\0';
                return 0;
            }
            (*string)[32 * i + j] = c;
        }
    }
    return 0;
}


void printl (char *string)
{
    while(string[0])
    {
        putchar((string++)[0]);
    }
}

int get_array_string (char ***pointer_string_array)
{
    int k = -1;
    int l;
    int status = 0;
    char **temp = NULL, **list = NULL;

    *pointer_string_array = NULL;

    while(1)
    {
        ++k;

        temp = realloc(list, 32 * (k+1) * sizeof(char*));
        if(temp == NULL)
        {
            printf("Memory allocation failed!\n");
            free(list);
            return -1;
        }
        list = temp;

        for (l = 0; l < 32; ++l)
        {
            status = getl(&list[32 * k + l]);
            if (status == -1)
            {
                printf("String could not be safed!\n");
                free(list);
                return -1;
            }
            if (list[32 * k + l][0] == '\n' || list[32 * k + l][0] == '\0')
            {
                *pointer_string_array = list;
                free(list[32 * k + l]);
                list[32 * k + l] = NULL;
                return 0;
            }
        }
    }
    return 0;
}


void print_string_array (char **string_array)
{

    while((*string_array) != NULL)
    {
        printl(*string_array);
        string_array++;
    }
}


void make_capital_letter (unsigned char *x)          // checks if *x is a lower case letter
{                                           // if so, it turns it into capital letter
    if (*x >= 97 && *x <= 122)
    {
        *x = *x - 22;
    }
}

int sign (int x)
{
    if(x > 0)
    {
        return 1;
    }
    if(x < 0)
    {
        return -1;
    }
    return 0;
}

int compare_two_strings (char *string_1, char *string_2)
{
                                    // function returns 0, if two strings coincide
                                    // returns 1, if string_1 is greater
                                    // returns -1, if string_2 is greater
    unsigned char c_1, c_2;
    unsigned char *s1, *s2;

    s1 = (unsigned char *) string_1;
    s2 = (unsigned char *) string_2;

    if(s1 == NULL)
    {
        s1 = (unsigned char *) "\0";
    }
    if(s2 == NULL)
    {
        s2 = (unsigned char *) "\0";
    }


    do
    {
        c_1 = *s1++;
        c_2 = *s2++;

        make_capital_letter(&c_1);
        make_capital_letter(&c_2);

        if (c_1 == '\0')
        {
            return sign((int)c_1 - (int)c_2);
        }
    }
    while(c_1 == c_2);

    return sign((int)c_1 - (int)c_2);
}














