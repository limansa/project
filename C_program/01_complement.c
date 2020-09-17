#include <stdio.h>

int main (void)
{
//解讀負數就是2的補數 就是取1的補數(~)+1再放上正負號
//0xffff fffe -> 0x0000 0001 + 1 -> MSB = 1 so anser is -2

    int a = 5;
    printf("%d = 0x%x\n", a, a);
    printf("%d = 0x%x\n", ~a, ~a);
    
    unsigned int b = 5;
    printf("%u = 0x%x\n", b, b);
    printf("%u = 0x%x\n", ~b, ~b);

    signed int c = 5;
    printf("%d = 0x%x\n", c, c);
    printf("%d = 0x%x\n", ~c, ~c);

    unsigned int d = 0xffff; //2^16-1 = 65535
    unsigned int k = ~d; //0xffff 0000 // -(65535+1)
    printf("%d %d\n", d, k); // 
    printf("%u %u\n", d, k);
    printf("%x %x\n", d, k);
    return 0;
}