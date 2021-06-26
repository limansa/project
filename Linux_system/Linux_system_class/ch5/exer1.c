


#include <signal.h>
#include <stdio.h>
#include <unistd.h>


static int counter=0;
#define MAX 16
enum {DISABLE,ENABLE};
static int action_flag=DISABLE;

void set_enable(int sig);
void set_disable(int sig);
void alarm_hang(int sig);
void reset(int sig);

void set_enable(int sig) 
{
	printf("Enagle Signal-USR1 Received!\n");
	action_flag=ENABLE;

}

void set_disable(int sig)
{
	printf("Disle Signal-USR2 Received!\n");
	action_flag=DISABLE;

}


void alarm_hang(int sig) 
{
//	printf("ALARM !\n");
	
	if(action_flag==ENABLE)
		counter++;

	if (counter==MAX) counter=MAX;

	alarm(1);
}

void reset(int sig)
{
    if(action_flag!=ENABLE) return ;
	printf("RESET !\n");

	counter=0;	
}

int main() 
{
  signal(SIGUSR1,set_enable);
  signal(SIGUSR2,set_disable);
  signal(SIGALRM,alarm_hang);
  signal(SIGINT,reset);
  printf("Timer PID=%d\n",getpid());
  alarm(1);
  
  while (1)
    {
	 
	  if (counter>=MAX) { 
		  printf("OverFLow!\r");
		  
      }else 
          printf ("counter=%d\r", counter);
     fflush(stdout);	  
	  pause();
      
    }
    
return 0;    
}
