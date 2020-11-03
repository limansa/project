#include <stdio.h>
#include <stdlib.h>
/*
#include <stdlib.h>
void qsort(void *base, size_t nmemb, size_t size,
          int (*compar)(const void *, const void *));
*/

#ifdef cmpstringp
#include <string.h>
static int cmpstringp(const void *p1, const void *p2)
{
   /* The actual arguments to this function are "pointers to
      pointers to char", but strcmp(3) arguments are "pointers
      to char", hence the following cast plus dereference */

   return strcmp(* (char * const *) p1, * (char * const *) p2);
}
#endif

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char *argv[])
{
#ifdef cmpstringp
    int j;
    if (argc < 2) {
       fprintf(stderr, "Usage: %s <string>...\n", argv[0]);
       exit(EXIT_FAILURE);
    }
    qsort(&argv[1], argc - 1, sizeof(char *), cmpstringp);
    for (j = 1; j < argc; j++)
        puts(argv[j]);
#endif
    #define NUMBER 3
    int a[NUMBER] = {5, 3, 7};
    int j = 0;
    qsort(a, NUMBER, sizeof(int), cmpfunc);
    for (j=0; j<NUMBER; j++) {
        printf("%d, ", a[j]);
    }

    exit(EXIT_SUCCESS);
}
