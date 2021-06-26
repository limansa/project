#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
struct message {

 int len;
 char buf[32];


}; 
void *print_message_function( void *ptr );
int main()
{
  pthread_t thread1;

  char *message1 = "Hello world";


 void *thread_result=0;
  pthread_create( &thread1, NULL, print_message_function,(void*) message1);

 // sleep(2);
// pthread_cancel(thread1);

 pthread_join( thread1, &thread_result);
  if (thread_result!=0) {
  printf("Thread 1 returns: %s\n",((struct message *)thread_result)->buf);
  printf("Thread 1 returns: %d\n",((struct message *)thread_result)->len);
  free(thread_result);
  }
  return 0;
}


void *print_message_function( void *ptr )
{


        int i;
	char *m;
	struct message *p=(struct message *)malloc(sizeof(struct message));
 	assert(p);
	m=(char *)ptr;	
 	for (i=0;m[i];i++) {
          p->buf[i]=toupper(m[i]); 
         }
	p->len=i;
	
	sleep(10);	
//*	return (void *) p;
	pthread_exit((void *) p);
}
