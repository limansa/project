#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>

void update_time(int sig);


int main()
{

	signal(SIGALRM,update_time);
	alarm(1);
       while (1)
		    ;
//        pause();
        
}

void update_time(int sig)
{

    time_t timeval;
    
    char *p;
    

    time(&timeval);

    p = (char *)ctime(&timeval);

   p[strlen(p)-1]='\0';
   printf("%s\r",p);
   

    fflush(stdout);
  
    alarm(1);


}

