#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <fcntl.h>
#include <errno.h>
#include <string.h>

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

    time_t timeval;
    char timeString[25];
    char *p;
    int i;

    time(&timeval);
/*
    strncpy(timeString, (const char *)ctime(&timeval), 24);
    printf("%s\r", timeString);
    fflush(stdout);
*/
    p = (char *)ctime(&timeval);
    for (i=0; i<strlen(p)-1; ++i) {
      printf("%c", *(p+i));
    }
    printf("\r");
    fflush(stdout);
//    printf("%s\b \b\r", (char *)ctime(&timeval));
  
    alarm(1);


}

