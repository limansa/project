/*
* rdfifo.c - Create a FIFO and read from it
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msg_header.h"

int main(void)
{
	
	int len; /* Bytes read from FIFO */
	char buf[PIPE_BUF];
	mode_t mode = 0777;
	int res;
        int msgid;
  	MSG mymsg;
	/* First, we set up the message queue. */

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
	/* Read and display message */
      if (msgrcv(msgid, (void *)&mymsg, 64,
                   1, 0) == -1) {
            fprintf(stderr, "msgrcv failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }

       printf("type=%ld-->%s\n", mymsg.type, mymsg.str);

      exit(EXIT_SUCCESS);
}
