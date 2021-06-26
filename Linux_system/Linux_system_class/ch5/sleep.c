#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

static void sig_alrm(int signo);
int mysleep(unsigned int nsecs);

static void sig_alrm(int signo)
{
	return;	
}

int mysleep(unsigned int nsecs)
{
//	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
//		return(nsecs);
	alarm(nsecs);		
	pause();		
	return( alarm(0) );	
}

int main()
{

  int x=5;
  int y=-1;
  time_t timeval;
    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
           return(0);


  (void)time(&timeval);
  printf("I go to  sleep  (%d seconds)\n",x);
  printf("The date is: %s\n", ctime(&timeval));
  y=mysleep(x);
  (void)time(&timeval);
  printf("i wake up ..,y=%d\n",y);
  printf("The date is: %s\n", ctime(&timeval));
  


 return 0;

}
