#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
void *print_message_function( void *ptr );
main()
{
pthread_t thread1, thread2;
char *message1 = "Thread 1 Hi";
char *message2 = "Thread 2 World";
int iret1, iret2;

 void *thread_result, *thread_result2;

iret1 = pthread_create( &thread1, NULL, print_message_function,
(void*) message1);
iret2 = pthread_create( &thread2, NULL, print_message_function,
(void*) message2);
/* Wait till threads are complete before main continues. Unless we */
/* wait we run the risk of executing an exit which will terminate */
/* the process and all threads before the threads have completed. */

pthread_join( thread1, &thread_result);
pthread_join( thread2, &thread_result2);

printf("Thread 1 returns: %d\n",*(int *)thread_result);
printf("Thread 2 returns: %d\n",*(int *)thread_result2);

free(thread_result);
free(thread_result2);

exit(0);
}


void *print_message_function( void *ptr )
{

	char *message;

	int *plen=(int *)malloc(sizeof(int));
	*plen=strlen(ptr);
	
	message = (char *) ptr;
//	printf("%s \n",plen);
        pthread_exit((void *)plen);

}
