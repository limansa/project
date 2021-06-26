#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>
struct message {

 char buf[32];
 int len;

}; 
void *print_message_function( void *ptr );
int main()
{
pthread_t thread1;
char *message1 = "Thread 1 Hello world";


 void *thread_result;
  pthread_create( &thread1, NULL, print_message_function,(void*) message1);

 pthread_join( thread1, &thread_result);

 printf("Thread 1 returns: %s\n",((struct message *)thread_result)->buf);
 printf("Thread 1 returns: %d\n",((struct message *)thread_result)->len);

free(thread_result);

  return 0;
}


void *print_message_function( void *ptr )
{



	struct message *p=(struct message *)malloc(sizeof(struct message));
 	assert(p);
	p->len=strlen(ptr);
	strncpy(p->buf,ptr,32);
	
	return (void *) p;
}
