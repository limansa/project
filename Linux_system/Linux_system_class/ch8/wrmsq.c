/*
* wrmsq.c - Write to a "well-known" Message Queue
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msg_header.h"

int main(void)
{

char buf[PIPE_BUF]; /* Ensure atomic writes */
time_t tp; /* For time call */

 int msgid;
 int len;
 
/* Identify myself */
printf("I am %d\n", getpid());
   
   MSG mymsg;
   memset(&mymsg,0,sizeof(MSG));


/* First, we set up the message queue. */
 
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
/* Generate some data to write */
while(1) {
/* Get the current time */
    time(&tp);
/* Create the string to write */
     len = sprintf(buf, "wrfifo %d sends %s", getpid(), ctime(&tp));
     mymsg.type = 1;
   
        strcpy(mymsg.str, buf);
	printf("%s\n",mymsg.str);

        if (msgsnd(msgid, (void *)&mymsg,64, 0) == -1) {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
     sleep(3);
  }

   if (msgctl(msgid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
exit(EXIT_SUCCESS);
}
