#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <assert.h> //assert
#include <unistd.h> //sleep
#include <signal.h> //pthread_kill
#include <errno.h> //ESRCH EINVAL
#include <sys/types.h> //getpid
#include <unistd.h> //getpid


struct message {
 char buf[32];
 int len;
};

int is_thread_live(pthread_t thread_id);
void *print_message_function( void *ptr );

int main()
{
    printf("[T0] PID=%d\n", getpid());
    char *message1 = "Hello world"; //Share memory
    void *thread_result;

    pthread_t t1_id;
    pthread_create( &t1_id, NULL, print_message_function,(void*) message1);
    printf("[T0] pthread_self[%ld] create pthread %ld\n", pthread_self(), t1_id);
    int i = 0;
    while (i < 10) {
        i ++;
        printf("[T0] The %d : %s\n", i, is_thread_live(t1_id)?"live":"dead");
        sleep(1);
    }
    pthread_join( t1_id, &thread_result); //Need to provide the location of pointer
    printf("[T0] T1 returns: %s\n",((struct message *)thread_result)->buf);
    printf("[T0] T1 returns: %d\n",((struct message *)thread_result)->len);

    free(thread_result);
    return 0;
}

void *print_message_function( void *ptr )
{
    char *thread_message = "Thread created";
    printf("[T1] pthread_self[%ld] message [%s]\n", pthread_self(), (char*)ptr);
    int i = 0;
    while (i < 3) {
        i ++;
        printf("[T1] the %d times live\n", i);
        sleep(1);
    }
    struct message *p=(struct message *)malloc(sizeof(struct message));
    assert(p);

    p->len=strlen(thread_message);
    strncpy(p->buf, thread_message, 32);

    printf("[T1] leave\n");
    return (void *) p; //Return pointer
}

int is_thread_live(pthread_t thread_id)
{
    int ret = pthread_kill(thread_id, 0);
    if (ret == ESRCH) {
        printf("No thread could be found corresponding to that specified by the given thread ID.\n");
        return 0;
    } else if (ret == EINVAL) {
        printf("The thread ID specified by thread is not valid.\n");
        printf("The value of sig is incorrect or is not the number of a supported signal.\n");
        return 0;
    }
    printf("thread_id %ld is live ret = %d\n", thread_id, ret);
    return 1;
}