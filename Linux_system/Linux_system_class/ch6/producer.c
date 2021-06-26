/*  Producer Consumer example using pthreads

  This program implements the classical producer consumer problem

  using POSIX standard pthreads.  It compiles and runs on most

  Unix systems.
  
  */



#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

 

int   q[5];                               // queue to hold produced numbers
int   first  = 0;                         // index into q of next free space
int   last   = 0;                         // index into q of next available number
int   numInQ = 0;                         // number of items in the queue



/* putOnQ is called by the producer threads to put a number on the queue */

void putOnQ(int x) {
   
      int ret;

     

      q[first] = x;                 // put item on the queue

      first = (first+1) % 5;

      numInQ++;                     // increment queue size

     
      printf("unlock(emtpy)\n");

    

}

 

/* getOffQ is called by consumer threads to retrieve a number

   from the queue.  The thread will be suspended if there is

   nothing on the queue. */

int getOffQ(void) {

      int thing;                    // item removed from the queue
      int ret=-1;
      /* wait if the queue is empty. */

      while (numInQ == 0) {
          ;
        

        }

    

      thing = q[last];              // get item from the queue

      last = (last+1) % 5;

      numInQ--;                     // decrement queue size

    

      return thing;

}

 

 

/*  Producer thread. */

void * prod(void *arg) {

      int   mynum;                  // thread number for identification

      int   i;

 

      mynum = *(int *)arg;

      for (i = 0; i < 3; i++) {

            sleep(i);               // wait just to make this interesting

            puts("putting");

            putOnQ(i+100*mynum);          // put number on the queue

            printf("put %d on queue\n", i+100*mynum);

      }

 }

 

 

/*  Consumer thread  */

void * con(void *arg) {

      int   i;

      int   stuff;                        // number received from queue

      for (i = 0; i < 6; i++) {

            puts("getting");

            stuff = getOffQ();            // get number from the queue

            printf("got %d from queue\n", stuff);

      }

 }

 

 

 

int  main()

{

 pthread_t threadp1;                      // Thread objects

 pthread_t threadp2;

 pthread_t threadc1;
 

 int zero = 0;  int one = 1;

 
 pthread_create(&threadc1, NULL, con,  NULL);   // start consumer thread

 pthread_create(&threadp1, NULL, prod, &zero);  // start first producer thread

// pthread_create(&threadp2, NULL, prod, &one);   // start second producer thread


 pthread_exit(NULL);                            // main thread quits


  return 0;

}
