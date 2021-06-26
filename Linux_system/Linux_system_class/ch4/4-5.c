#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
int main(void) {
char c = '!';
char buf[20];
int myfd;
int num_read=0;
pid_t child_pid;


if ((child_pid=fork()) == -1) {
perror("Failed to fork");
return 1;
}



if ((myfd = open("my.dat", O_RDWR )) == -1) {
perror("Failed to open file");
return 1;
}
/*
if ((child_pid=fork()) == -1) {
perror("Failed to fork");
return 1;
}
*/
while((num_read=read(myfd, &c,1))>0) {
	printf("Process %ld got %d byted %c\n",	(long)getpid(), num_read,c);
	sleep(1);
}

  close(myfd);



return 0;
}
