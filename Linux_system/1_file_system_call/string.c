#include <stdio.h>
#include <string.h>

int main ()
{
   int len;
   const char str1[] = "ABCD0123";
   const char str2[] = "C3";

    //strspn, strcspn - get length of a prefix substring
   len = strcspn(str1, str2);

   printf("Length of initial segment matching %d %s\n", len, str1+len);

   return 0;
}