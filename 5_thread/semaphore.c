#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
void *functionC();
int counter = 0;
sem_t semA;
#define NUM_THREADS 5
main()
{
    int rc;
    int i;
    pthread_t thread_id[NUM_THREADS];
    if (sem_init(&semA, 0, 1) == -1)
        perror("Failed to initialize semaphore semA");
    /* Create independent threads each of which will execute functionC */
    for (i=0;i<NUM_THREADS;i++) {
        if( (rc=pthread_create( &thread_id[i], NULL, &functionC, NULL)) )
        printf("Thread creation failed: %d\n", rc);
    }
    /* Wait till threads are complete before main continues. Unless we */
    /* wait we run the risk of executing an exit which will terminate */
    /* the process and all threads before the threads have completed. */
    for (i=0;i<NUM_THREADS;i++) {
    pthread_join( thread_id[i], NULL);
    if (sem_destroy(&semA) == -1)
    perror("Failed to destroy semA");
    exit(0);
}

void *functionC()
{
    int i=0;
    while(i< 10) {
        sem_wait(&semA);
        counter++;
        sem_post(&semA);
        i++;
    }
    printf("%d:Counter value: %d\n",pthread_self(),counter);
}