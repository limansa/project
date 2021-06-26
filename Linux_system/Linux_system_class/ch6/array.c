#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct array_struct {
  int * data;
  int size;
};




void *double_array( void *ptr );
main()
{
 pthread_t thread1;
 int iret1;
 void *thread_result;
  
  int Array[]={5,10,15,20};
  struct array_struct myarray={

   .data=Array,
   .size=sizeof(Array)/sizeof(Array[0])
  };


iret1 = pthread_create( &thread1, NULL,double_array,
(void*) &myarray);

pthread_join( thread1, &thread_result);

//printf("Thread 1 returns: %d\n",*(int *)thread_result);

//free(thread_result);

exit(0);
}

void *double_array( void *ptr )

{

	
   int i;
    struct array_struct *p=(struct array_struct *)ptr;
    int n=p->size;
     for (i=0;i<n;i++,p->data++)
         printf("%d \n",*(int *)(p->data));

   

}
