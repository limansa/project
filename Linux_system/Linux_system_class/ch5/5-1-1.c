#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static int counter=0;
static int action_flag=0;

void cmd_hang(int sig);
void alarm_hang(int sig);
void reset(int sig);

void cmd_hang(int sig) 
{
	printf("INT !\n");
	
	if(action_flag)
		action_flag = 0; //count
	else
		action_flag = 1; //stop	 	
}

void alarm_hang(int sig) 
{
	printf("ALARM !\n");
	
	if(!action_flag)
		counter++;

	alarm(1);
}

void reset(int sig)
{
	printf("RESET !\n");
	
	counter=0;	
}

int main() 
{
  signal(SIGINT,cmd_hang);
  signal(SIGALRM,alarm_hang);
  signal(SIGUSR1,reset);

  alarm(1);
  
  while (1)
    {
      printf ("counter=%d\n", counter);
      sleep (1);
    }
    
return 0;    
}
