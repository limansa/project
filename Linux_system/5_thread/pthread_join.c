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
void *T1( void *ptr );

int main()
{
    printf("[T0] ++++++\n");
    printf("[T0] PPID=%d PID=%d\n", getppid(), getpid());

    char *message1 = "Hello world"; //Share memory
    void *thread_result = NULL;

    pthread_t t1_id;
    pthread_create( &t1_id, NULL, T1,(void*) message1);
    printf("[T0] pthread_self[%ld] create pthread %ld\n", pthread_self(), t1_id);
    int i = 0;
    while (i < 10) {
        i ++;
        printf("[T0] The %d : %s\n", i, is_thread_live(t1_id)?"live":"dead");
        sleep(1);
    }
    pthread_join( t1_id, &thread_result); //Need to provide the location of pointer

    if (thread_result) {
        printf("[T0] T1 returns: %s\n",((struct message *)thread_result)->buf);
        printf("[T0] T1 returns: %d\n",((struct message *)thread_result)->len);
        free(thread_result);
    }
    printf("[T0] -------\n");
    return 0;
}

void *T1( void *ptr )
{
    printf("[T1] ++++++\n");
    char *thread_message = "T1 return result";
    printf("[T1] pid=%d pthread_self[%ld] message [%s]\n", getpid(), pthread_self(), (char*)ptr);
    int i = 0;
    while (i < 5) {
        i ++;
        printf("[T1] Keep alive %d\n", i);
        sleep(1);
    }
    struct message *p=(struct message *)malloc(sizeof(struct message));
    assert(p);
    p->len=strlen(thread_message);
    strncpy(p->buf, thread_message, 32);

    printf("[T1] -------\n");
    return (void *) p; //Return pointer
}

int is_thread_live(pthread_t thread_id)
{
    int ret = pthread_kill(thread_id, 0);
    if (ret == ESRCH) {
        printf("[ESRCH]No thread could be found corresponding to that specified by the given thread ID.\n");
        return 0;
    } else if (ret == EINVAL) {
        printf("[EINVAL]The thread ID specified by thread is not valid.\n");
        printf("[EINVAL]The value of sig is incorrect or is not the number of a supported signal.\n");
        return 0;
    }
    //printf("thread_id %ld is live ret = %d\n", thread_id, ret);
    return 1;
}