#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
void do_child(int data_pipe[], int pipe2[]) {
    char ch[10]; /* data received from the parent. */
    int c, rp, rc; /* return status of read(). */
    int i = 0; 

    close(data_pipe[1]);
    close(pipe2[0]);
    while ((rc = read(data_pipe[0], &c, 1)) > 0) {
        ch[i] = c - ('a'-'A');
        i++;
    }
	 ch[i]=0;
    write(pipe2[1],ch,i);
}

void do_parent(int data_pipe[], int pipe2[]) {
    char cmd[15] = "hello"; /* data received from the user. */
    char ch[15];
    int n;
    int rc; /* return status of getchar(). */
    close(data_pipe[0]);
    close(pipe2[1]);
    rc = write(data_pipe[1], cmd, strlen(cmd));
    fprintf(stderr,"Parsent send \"%s\" \n", cmd);
    if (rc == -1) { /* write failed - notify the user and exit */
        perror("Parent: write");
        close(data_pipe[1]);
        exit(1);
    }
    close(data_pipe[1]);
    n=read(pipe2[0], ch, sizeof(ch));
    printf("Get from child:%s\n", ch);
    exit(0);
}

int main(int argc, char* argv[])
{
    int data_pipe[2];
    int pipe2[2];
    int pid, rc, rc2;
    rc = pipe(data_pipe);
    rc2 = pipe(pipe2);
    if (rc == -1 || rc2 == -1) {
        perror("pipe");
        exit(1);
    }
    /* now fork off a child process, and set their handling routines. */
    pid = fork();
    switch (pid) {
        case -1: /* fork failed. */
            perror("fork");
            exit(1);
        case 0: /* inside child process. */
            do_child(data_pipe, pipe2); 
            break;
        default: /* inside parent process. */
            do_parent(data_pipe, pipe2);
    }
    return 0; /* NOT REACHED */
}
