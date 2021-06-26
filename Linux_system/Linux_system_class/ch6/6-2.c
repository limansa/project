#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h> // for sched_yield()
void thread1();
void thread2();
void cleanup(int counter1, int counter2);
#define NUM 20
int counter=0;
int main(int argc, char *argv[])
{
pthread_t thrd1, thrd2;
int ret;
/* Create the first thread */
ret = pthread_create(&thrd1, NULL ,(void *)thread1, (void *)0);
if(ret) {
perror("pthread_create: thread1");
exit(EXIT_FAILURE);
}
/* Create the second thread */
ret = pthread_create(&thrd2,NULL, (void *)thread2, (void *)0);
if(ret) {
perror("pthread_create: thread2");
exit(EXIT_FAILURE);
}
pthread_join(thrd2, NULL);
pthread_join(thrd1, NULL);
printf("total iterations: %d\n", counter);
exit(EXIT_SUCCESS);
}
void thread1()
{
int i=0;
while(i< NUM) {
printf("thread1 count: %d\n", i);
i++;
counter++;
//sched_yield();
}
}
void thread2()
{
int i=0;
while( i < NUM) {
printf("thread2 count: %d\n", i);
i++;
counter++;
//sched_yield();
}
}