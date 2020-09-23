#include <stdio.h>
#include <string.h>

void main () {
    char* str = "hello";
    char char_str1[] = {'h', 'e', 'l', 'l', 'o'}; //字元陣列
    char char_str[] = {'h', 'e', 'l', 'l', 'o', '\0'}; //字元字串
    int array [] = {1, 2, 3};
    printf("%s: sizeof(str)=%ld, strlen(str)=%ld\n", str, sizeof(str), strlen(str));
    printf("%s: sizeof(char_str1)=%ld, strlen(char_str1)=%ld\n", char_str1, sizeof(char_str1), strlen(char_str1));
    printf("%s: sizeof(char_str)=%ld, strlen(char_str)=%ld\n", char_str, sizeof(char_str), strlen(char_str));
    printf("sizeof(array)=%ld\n", sizeof(array));
    return;
}

/*
 Output:
    hello: sizeof(str)=8, strlen(str)=5  //sizeof(char*)=8 
    hellohello: sizeof(char_str1)=5, strlen(char_str1)=10
    hello: sizeof(char_str)=6, strlen(char_str)=5
    sizeof(array)=12
 * */