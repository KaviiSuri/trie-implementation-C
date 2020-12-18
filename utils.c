#include <stdio.h>

void printArray(char chars[], int len)
{
    int i;
    for (i = 0; i < len; i++)
        printf("%c", chars[i]);
    printf("\n");
}