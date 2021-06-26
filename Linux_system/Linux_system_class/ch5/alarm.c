#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <fcntl.h>
#include <errno.h>

void update_time(int sig);


int main()
{

	signal(SIGALRM,update_time);
	alarm(1);
       while (1)
        pause();
        
}

void update_time(int sig)
{
   static int i=0;
   struct timeval start;

   gettimeofday(&start, NULL);

   printf("%3d @%u\n",i++,((unsigned)(start.tv_sec * 1000000 + start.tv_usec))); 
   


    alarm(1);


}



