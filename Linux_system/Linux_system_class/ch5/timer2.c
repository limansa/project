#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <fcntl.h>
#include <errno.h>


#define TRUE 1
#define FALSE 0
void kill_me();
void event_loop(int sig);
#define EVENT_EXIT 5
static int timer = 0;
static int reset= FALSE;
static int gotdata=0;


void sighandler(int signo)
{

    printf(" got SIGIO singal\n");
    if (signo==SIGIO)
        gotdata++;
    return;
}





int main()
{
	printf("my pid is %ld\n",getpid());
	signal(SIGALRM,event_loop);
	signal(SIGIO,sighandler);
        fcntl(STDIN_FILENO, F_SETOWN, getpid());
	fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | FASYNC);

	alarm(1);

       //fcntl(STDIN_FILENO, F_SETFL, fcntl(0,F_GETFL) | O_NONBLOCK); /* stdin */

	while (1) {
	
	  /* this only returns if a signal arrives */
        sleep(86400); /* one day */
        if (!gotdata)
              continue;
	 printf(".");
	  char ch;
          ch=getchar();
          if (ch=='\n') 
               reset=TRUE;

        gotdata=0;
    }





	
}

void kill_me()
{

// if (kill(getpid(), SIGKILL) < 0 )
 if (raise(SIGKILL) < 0 )
     perror ("Failed to kill myself");

}




void event_loop(int sig)
{

 extern int timer ;
 timer++;
  
   printf("timer=%d\b\r\n",timer);

   if (reset==TRUE) {
	timer=0;
	reset=FALSE;
   }


 if (timer==EVENT_EXIT)
       kill_me();

   alarm(1);


}



