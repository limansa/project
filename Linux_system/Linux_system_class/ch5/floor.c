#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <fcntl.h>
#include <errno.h>
#define MAX_FLOOR 19
#define MIN_FLOOR 1
void move(int sig);
void up(int sig);
void down(int sig);
void stop(int sig);

int n_floor=MIN_FLOOR;
enum ACT {UP,DOWN, STOP};

enum ACT action;

int main()
{
	printf("my pid is %ld\n",getpid());
	action=STOP;
	signal(SIGALRM,move);
	signal(SIGHUP,stop);
	signal(SIGUSR1,up);
	signal(SIGUSR2,down);
	alarm(1);
  	while (1) 
	    pause();	
   return 0; 

	
}


void stop(int sig)
{
  action=STOP;
  
}

void up(int sig)
{
  action=UP;
  
}

void down(int sig)
{

  action=DOWN;
}




void move(int sig)
{

  extern int n_floor ;
   

   switch (action) 
   {
     case STOP:

         break;
     case UP:
 	n_floor++;
         break;

     case DOWN:
        n_floor--;
         break;	 

  } 

 if (n_floor>MAX_FLOOR) n_floor=MAX_FLOOR;
 if (n_floor<MIN_FLOOR) n_floor=MIN_FLOOR;
       
 fprintf(stderr,"current floor=%3d\b\r",n_floor);


   alarm(1);


}



