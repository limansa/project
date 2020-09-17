#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 #include <unistd.h> //sleep
void *functionC();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;
#define NUM_THREADS 5

void main()
{
    int rc;
    int i;
    pthread_t thread_id[NUM_THREADS];
    /* Create independent threads each of which will execute functionC */
    for (i=0;i<NUM_THREADS;i++) {
        if( (rc=pthread_create( &thread_id[i], NULL, &functionC, NULL)) )
            printf("Thread creation failed: %d\n", rc);
#define MAX_THREAD_NAME_SIZE 16
        char thread_name [MAX_THREAD_NAME_SIZE] = {};
        sprintf(thread_name, "T%d ", i);
        pthread_setname_np(thread_id[i], thread_name);
        //printf("create %s for %ld\n", thread_name, thread_id[i]);
    }
    /* Wait till threads are complete before main continues. Unless we */
    /* wait we run the risk of executing an exit which will terminate */
    /* the process and all threads before the threads have completed. */
    for (i=0;i<NUM_THREADS;i++)
        pthread_join( thread_id[i], NULL);
    exit(0);
}

void *functionC()
{
    int i=0;
    sleep(1);//for late to use pthread_getname_np
    char thread_name [MAX_THREAD_NAME_SIZE] = {};
    pthread_getname_np(pthread_self(), thread_name, MAX_THREAD_NAME_SIZE);
    //printf("get %s for %ld\n", thread_name, pthread_self());
    while(i< 10) {
        pthread_mutex_lock( &mutex1 );
        counter++;
        pthread_mutex_unlock( &mutex1 );
        i++;
        printf("[%s] counter = %d\n", thread_name, counter);
        sleep(1);
    }
    printf("[%s] Counter value: %d --------\n", thread_name, counter);
}