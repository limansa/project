/* The sender program is very similar to msg1.c. In the main set up, delete the
 msg_to_receive declaration and replace it with buffer[BUFSIZ], remove the message
 queue delete and make the following changes to the running loop.
 We now have a call to msgsnd to send the entered text to the queue. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#define MAX_TEXT 512

struct my_msg_st {
    long int my_msg_type;
    char some_text[MAX_TEXT];
};

int main()
{
    int running = 1;
    struct my_msg_st some_data;
    int msgid;
    char buffer[BUFSIZ];
    time_t tp;

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    some_data.my_msg_type=1;
    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    while(running) {

	time(&tp);
	sprintf(buffer, "wrfifo %d sends %s", getpid(), ctime(&tp));
//        printf("Enter some text: ");
  //      fgets(buffer, BUFSIZ, stdin);
 
        some_data.my_msg_type = some_data.my_msg_type%2+1 ;
        strcpy(some_data.some_text, buffer);
	fprintf(stderr,"%s",buffer);    
        if (msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1) {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp(buffer, "end", 3) == 0) {
            running = 0;
        }
	sleep(1);
    }

    exit(EXIT_SUCCESS);
}
