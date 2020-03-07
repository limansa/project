#include <stdlib.h>
#include <unistd.h>

int main ()
{
    int i = 0;
    while(1) {
        printf("The %d times\n", i);
        i++;
    }
    return 0;
}