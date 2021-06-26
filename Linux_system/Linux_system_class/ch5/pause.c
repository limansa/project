#include <signal.h>
#include <stdio.h>
#include <unistd.h>
static int sigreceived = 0;
void sig_usr1 (int sig) 
{
  sigreceived = 1;
  printf ("%s - I got signal %d ,sigreceived=%d\n", __func__, sig, sigreceived);
} 
void sig_int (int sig) 
{
  printf ("%s - I got signal %d ,sigreceived=%d\n", __func__, sig, sigreceived);
  
} 

int main()
{
  int signum;
  sigset_t sigset;
  struct sigaction act, act1;


  act.sa_handler = sig_usr1;
  act1.sa_handler = sig_int;
  sigemptyset (&act.sa_mask);
  act.sa_flags = 0;
  sigemptyset (&act1.sa_mask);
  act1.sa_flags = 0;
  if (sigaction (SIGUSR1, &act, 0)==-1) perror("usr1:");
  if(sigaction (SIGINT, &act1, 0)==-1) perror("int");
  while (sigreceived == 0)
    {
      printf ("only waits for SIGUSR1\n");
      pause ();
    }
  
  printf ("I got SIGUSR1, exit now !\n");
  
  return 0;
}



