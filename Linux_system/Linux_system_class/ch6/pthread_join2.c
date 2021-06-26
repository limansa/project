#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>

struct message {
 char buf[32];
 int len;

}; 

struct msg {
  void *arg;	
  struct message m;


};





void *print_message_function( void *ptr );
int main()
{
pthread_t thread1;
char *message1 = "Thread 1 Hello world";

 void *thread_result;
  struct msg *p=(struct msg *)malloc(sizeof(struct msg));
  p->arg=(void *)message1;

  pthread_create( &thread1, NULL, print_message_function,(void*) p);

 pthread_join( thread1, &thread_result);

  printf("Thread 1 returns: %s\n",((struct msg *)thread_result)->m.buf);
 printf("Thread 1 returns: %d\n",((struct msg *)thread_result)->m.len);

free(p);

  return 0;
}


void *print_message_function( void *ptr )
{



//	struct message *p=(struct message *)malloc(sizeof(struct message));
 	assert(ptr);
	struct msg *p=(struct msg *)ptr;
	p->m.len=strlen((char *)p->arg);	
	strncpy(p->m.buf,p->arg,32);
	
	return (void *)ptr;
}
