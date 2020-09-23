#include <stdio.h>
// start++ 指標的++ 是加一個單位
void show_1d(int *start, int* end)
{
    int i = 0;
    for (; start < end; start++) {
        i ++;
        printf("a[%d]=%-5d<--%p\n", i, *start, start);
    }
}

int main()
{
    int i = 0;
    int a[3] = {5, -2, 17};
    show_1d(a, a+3);
    a[1] = 100;
    show_1d(&a[0], a+3);
    return 0;
}
