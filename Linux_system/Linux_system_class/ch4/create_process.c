#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int create_process (int n);

int main (int argc, char *argv[]) 
{


 if (argc != 2) {
	fprintf(stderr, "Usage: %s processes\n", argv[0]);
	return 1;
 }
 create_process(atoi(argv[1]));
 
 sleep(1); 

 return 0;

}
int create_process (int n)
{

 pid_t childpid=0;
 int i;

 for (i = 1; i < n; i++)
  if ((childpid = fork())==0) {
  fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
    i, (long)getpid(), (long)getppid(), (long)childpid);
   break;
  }


 return i;
 
  


}


