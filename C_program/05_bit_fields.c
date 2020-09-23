#include <stdio.h>
int main() {
    struct {
        unsigned int code1:16;
        unsigned int code2:16;
        unsigned int code3:8; //0~256
    } prcode;
    //40 bit => alignment 64 bit  
    prcode.code1 = 0;
    prcode.code2 = 3;
    printf("sizeof(prcode)=%ld\n", sizeof(prcode));
    printf("prcode.code1=%d\n", prcode.code1);
    return 0;
}

/* output:
 * sizeof(prcode)=8
 * prcode.code1=0
 */