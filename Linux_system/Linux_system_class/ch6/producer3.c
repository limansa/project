/*  Producer Consumer example using pthreads

  This program implements the classical producer consumer problem

  using POSIX standard pthreads.  It compiles and runs on most

  Unix systems.
  
  */



#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
 sem_t mutex;
 sem_t empty;
 sem_t full;
int   q[5];                               // queue to hold produced numbers
int   first  = 0;                         // index into q of next free space
int   last   = 0;                         // index into q of next available number
int   numInQ = 0;                         // number of items in the queue

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;    // mutual exclusion lock
//pthread_mutex_t empty = PTHREAD_MUTEX_INITIALIZER;    // synchronization lock
//pthread_mutex_t full = PTHREAD_MUTEX_INITIALIZER;    // synchronization lock

 

/* putOnQ is called by the producer threads to put a number on the queue */

void putOnQ(int x) {
	/*
      while (numInQ == 4){ 
	printf("is FULL!\n");
	pthread_mutex_lock(&full);
	}
	*/
      while (numInQ == 4){
	printf("is FULL!\n");
	sem_wait(&full);
	}
      //pthread_mutex_lock(&mutex);   // lock access to the queue
	sem_wait(&mutex);
      q[first] = x;                 // put item on the queue

      first = (first+1) % 5;

      numInQ++;                     // increment queue size

      //pthread_mutex_unlock(&mutex); // unlock queue
	sem_post(&mutex);
      //pthread_mutex_unlock(&empty); // start a waiting consumer
	sem_post(&empty);
}

 

/* getOffQ is called by consumer threads to retrieve a number

   from the queue.  The thread will be suspended if there is

   nothing on the queue. */

int getOffQ(void) {

      int thing;                    // item removed from the queue

      /* wait if the queue is empty. */
	/*
      while (numInQ == 0){
	printf("is EMPTY!\n");
	 pthread_mutex_lock(&empty);
	}*/	
      while(numInQ == 0){
	printf("is EMPTY!\n");
	// pthread_mutex_lock(&empty);
	sem_wait(&empty);
	}	
      //pthread_mutex_lock(&mutex);   // lock access to the queue
	sem_wait(&mutex);
      thing = q[last];              // get item from the queue

      last = (last+1) % 5;

      numInQ--;                     // decrement queue size

     // pthread_mutex_unlock(&mutex); // unlock queue
	sem_post(&mutex);
     // pthread_mutex_unlock(&full); // start a waiting consumer
	sem_post(&full);
      return thing;

}

 

 

/*  Producer thread. */

void * prod(void *arg) {

      int   mynum;                  // thread number for identification

      int   i;

 
      sleep(2);
      mynum = *(int *)arg;

      for (i = 0; i < 5; i++) {

            if(i==2)
	       sleep(10);               // wait just to make this interesting

            puts("putting");

            putOnQ(i+100*mynum);          // put number on the queue

            printf("put %d on queue\n", i+100*mynum);

      }

 }

 

 

/*  Consumer thread  */

void * con(void *arg) {

      int   i;

      int   stuff;                        // number received from queue

      for (i = 0; i < 7; i++) {
            puts("getting");
            stuff = getOffQ();            // get number from the queue

            printf("got %d from queue\n", stuff);

      }

 }

 

 

 

int  main()

{
  sem_init(&empty,0,0);
  sem_init(&full,0,1);
  sem_init(&mutex,0,1);

 pthread_t threadp1;                      // Thread objects

 pthread_t threadp2;

 pthread_t threadc1;

 int zero = 0;  int one = 1;

 

 pthread_create(&threadp1, NULL, prod, &zero);  // start first producer thread

 pthread_create(&threadp2, NULL, prod, &one);   // start second producer thread

 pthread_create(&threadc1, NULL, con,  NULL);   // start consumer thread

 pthread_exit(NULL);                            // main thread quits


  return 0;

}
