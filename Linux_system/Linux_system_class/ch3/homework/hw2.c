#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define length  (sizeof(string) / sizeof(string[0]))

char string[][12] = { "Linux", "programming", "Embedded", "Android", "ittraining" };

static int cmpstringp(const void *p1, const void *p2)
{
    return strcmp(*(char * const *)p1, *(char * const *)p2);
}

int main()
{
    char* stringindex[length];
    int i;

    // copy pointer
    for (i=0; i<length; i++)
    {
        stringindex[i] = string[i];
    }

    qsort(stringindex, length, sizeof(stringindex[0]), cmpstringp);

    printf("\nSorted data:\n");

    for (i=0; i<length; i++)
    {
        printf("%d = %s\n", i, stringindex[i]);
    }

    printf("After qsort, origonal array:\n");

    for (i=0; i<length; i++)
    {
        printf("string[%d] = %s\n", i, string[i]);
    }

    exit(EXIT_SUCCESS);
}