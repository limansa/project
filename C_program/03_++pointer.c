#include <stdio.h>

void main ()
{
    int a[2] = {100, 200};
    int b[2] = {300, 400};
    int *p1, *p2, *p3;
    p1 = p2 = a;
    p3 = b;
    printf("*p1=%d, *p2=%d, *p3=%d\n", *p1, *p2, *p3);
    printf("*p1++=%d, *++p2=%d, (*p3)++=%d\n", *p1++, *++p2, (*p3)++);
    printf("*p1=%d, *p2=%d, *p3=%d\n", *p1, *p2, *p3);
}

/* Output:
    *p1=100, *p2=100, *p3=300
    *p1++=100, *++p2=200, (*p3)++=300
    *p1=200, *p2=200, *p3=301
*/