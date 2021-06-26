\
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
int x;
pid_t pid;
x = 0;
pid=fork();

//if (pid==0) {
//   setpgid(getpid(),getpid());

//}

fprintf(stderr, "PID:%ld PPID:%ld PGID:%ld\n",
	 (long)getpid(), (long)getppid(), (long)getpgrp());

return 0;

}
