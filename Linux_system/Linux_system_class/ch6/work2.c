#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>
#define size_of_arr(ar) sizeof(ar)/sizeof(ar[0])
int len;
void *count_function( void *ptr );
int main()
{
 int a[]={5,10,15,20};
 pthread_t thread1;
 int i;
 void *thread_result;
 len =size_of_arr(a);
 printf("a:%x\n",a);
 pthread_create( &thread1, NULL, count_function,(void*)a);

 pthread_join( thread1,(void *) &thread_result);
// printf("%x\n",&thread_result);
// for(i=0;i<len;i++)
 printf("Thread 1 returns: %d\n",*(((int *)thread_result)));
 printf("%x\n",thread_result);
 free(thread_result);

  return 0;
}

void * count_function( void *ptr )
{
   	int *b=malloc(sizeof(int));
	//b=(int *)ptr;	
	*b=0;
	int i;
	for (i=0;i<len;i++)
	   *(b) += *(((int *)ptr)+i);
//	   printf("thread:%d\n",*(b+i));
//	printf("%x\n",&b);	
	return (void *) b;
}
