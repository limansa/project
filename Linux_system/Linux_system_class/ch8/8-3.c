#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <termios.h>
#include <string.h>
void setup_console(int t);
/* this routine handles the work of the child process. */

void do_child(int data_pipe[]) {
char c; /* data received from the parent. */
int rc; /* return status of read(). */
/* first, close the un-needed write-part of the pipe. */
close(data_pipe[1]);
/* now enter a loop of reading data from the pipe, and printing it */
while ((rc = read(data_pipe[0], &c, 1)) > 0) {
   putchar(toupper(c));
}
exit(0);
}
/* this routine handles the work of the parent process. */

void do_parent(int data_pipe[])
{
int c; /* data received from the user. */
int rc; /* return status of getchar(). */
/* first, close the un-needed read-part of the pipe. */
// close(data_pipe[0]);
while ((c = getchar()) > 0) {
/* write the character to the pipe. */
rc = write(data_pipe[1], &c, 1);
if (rc == -1) { /* write failed - notify the user and exit */
perror("Parent: write");
}
}
close(data_pipe[1]);
exit(0);


}
int main(int argc, char* argv[])
{
int data_pipe[2];
int pid;
int rc;
setup_console(1);

/* first, create a pipe. */
rc = pipe(data_pipe);
if (rc == -1) {
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
do_child(data_pipe); break;
/* NOT REACHED */
default: /* inside parent process. */
do_parent(data_pipe);
/* NOT REACHED */
}

setup_console(0);
return 0; /* NOT REACHED */



}


void setup_console(int t)
{

        struct termios our_termios;
        static struct termios old_termios;

        if(t)
        {
                tcgetattr(0, &old_termios);
                memcpy(&our_termios, &old_termios, sizeof(struct termios));
                our_termios.c_lflag &= !(ECHO | ICANON);
                //our_termios.c_lflag &= !(ECHO );
                tcsetattr(0, TCSANOW, &our_termios);
        }
        else
                tcsetattr(0, TCSANOW, &old_termios);

}

