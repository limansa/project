#include <stdio.h>
#include <time.h>
#include <unistd.h>

static inline time_t get_timestamp_in_ms() {
    struct timespec ts = {0};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000 + ts.tv_nsec/1000000;
}

int function(int time) {
    int i = 0;
    while (i < time) {
        sleep(1);
        i++;
        printf("time=%d i=%d\n", time, i);
    }
    return 0;
}

//Method 1:
typedef int(*FP)(int); //定義FP 是一種function pointer type
FP fp = function;
//Method 2:
//int (*fp)(int);
//fp = function;

int measure_execution_time(FP fp, int pram) {
    time_t start, end;
    start = get_timestamp_in_ms();
    fp(pram);
    end = get_timestamp_in_ms();
    printf("Total cost time=%ld ms [%ld, %ld]\n", end-start, start, end);
    return end-start;
}

int main() {
    time_t time;
    
    time = measure_execution_time(fp, 2);
    return 0;
}