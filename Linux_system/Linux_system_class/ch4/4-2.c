

#include <stdio.h>
#include <unistd.h>
int main(void) {
int x;
pid_t pid;
x = 0;
pid=fork();
if (pid==0) x = 1;
printf("I am process %ld, my ppid=%ld and my x is %d\n",
	   	(long)getpid(),(long)getppid(),x);
return 0;
}
