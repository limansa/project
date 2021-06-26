#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *functionC();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;
#define NUM_THREADS 5
main()
{
int rc;
int i;
pthread_t thread_id[NUM_THREADS];
/* Create independent threads each of which will execute functionC */
for (i=0;i<NUM_THREADS;i++) {
    if( (rc=pthread_create( &thread_id[i], NULL, &functionC, NULL)) )
}
printf("Thread creation failed: %d\n", rc);
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
    while(i< 10) {
        pthread_mutex_lock( &mutex1 );
        counter++;
        pthread_mutex_unlock( &mutex1 );
        i++;
    }
printf("Counter value: %d\n",counter);
}