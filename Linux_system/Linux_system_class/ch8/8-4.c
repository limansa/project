int main(int argc, char* argv[])
{
int data_pipe[2];
int pid;
int rc;
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
return 0; /* NOT REACHED */
}