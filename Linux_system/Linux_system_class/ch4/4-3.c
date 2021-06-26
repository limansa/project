#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
pid_t pid;
char *message;
int n,i=100,stat_val;
printf("fork program starting\n");
pid = fork();
switch(pid)
{
case -1:
perror("fork failed");
exit(1);
case 0:
message = "child";
n = 3;
break;
default:
message = "parent";
n = 5;
break;
}
for(; n > 0; n--) {
printf("%d [%d] --%s\n",i,n,message);
sleep(1);
}
exit(0);
}