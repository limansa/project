


#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct _timer {

 unsigned int initval:8;
 unsigned int curval :8;
 unsigned int cmpval :8; 
 unsigned int enable :1;
 unsigned int flag   :3;
 unsigned int res    :4; /*reserved*/

}TIMER;




TIMER t1;
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
	t1.enable=ENABLE;

}

void set_disable(int sig)
{
	printf("Disle Signal-USR2 Received!\n");
	action_flag=DISABLE;
	t1.enable=DISABLE;

}


void alarm_hang(int sig) 
{
//	printf("ALARM !\n");
	
	if(t1.enable==ENABLE)
		t1.curval--;

	if (t1.curval==0) t1.curval=t1.initval;

	alarm(1);
}

void reset(int sig)
{
    if(t1.enable!=ENABLE) return ;
	printf("RESET !\n");

	t1.curval=0;	
}

int main() 
{
  memset(&t1,0,sizeof(TIMER));
  t1.initval=MAX;
  t1.cmpval=8;
  t1.curval=t1.initval;
  printf("%d\n",t1.initval);
  signal(SIGUSR1,set_enable);
  signal(SIGUSR2,set_disable);
  signal(SIGALRM,alarm_hang);
  signal(SIGINT,reset);
  printf("Timer PID=%d\n",getpid());
  alarm(1);
  
  while (1)
    {
	  if (t1.enable!=1) goto sleep;

	  if (t1.curval==0) { 
		  t1.curval=t1.initval;		  
      }else if (t1.curval>=t1.cmpval) {
          printf ("1");
	  }else 
		  printf("0");
	 
     fflush(stdout);	  
sleep:	 
	  pause();
      
    }
    
return 0;    
}
