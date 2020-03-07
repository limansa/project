#include <signal.h>
#include <stdio.h>
#include <unistd.h>
void ouch (int sig)
{
  printf ("OUCH! - I got signal %d\n", sig);
}

void show_mask()
{
        sigset_t sigset;

        if (sigprocmask(SIG_SETMASK, NULL, &sigset) < 0)
                fprintf(stderr, "sigprocmask error\n");

        if (sigismember(&sigset, SIGINT))       printf("SIGINT ");
        if (sigismember(&sigset, SIGQUIT))      printf("SIGQUIT ");
        if (sigismember(&sigset, SIGUSR1))      printf("SIGUSR1 ");
        if (sigismember(&sigset, SIGALRM))      printf("SIGALRM ");
        printf("\n");
}



void set_sigmask()

{
sigset_t newsigset;

if ((sigemptyset(&newsigset) == -1) ||
    (sigaddset(&newsigset, SIGINT) == -1))
   perror("Failed to initialize the signal set");
else if (sigprocmask(SIG_BLOCK, &newsigset, NULL) == -1)
   perror("Failed to block SIGINT");


}

int main ()
{
  struct sigaction act;
  act.sa_handler = ouch;
  show_mask();
  sigemptyset (&act.sa_mask);
  show_mask();
  act.sa_flags = 0;
  sigaction (SIGINT, &act, 0);
  set_sigmask();
  show_mask();


  while (1)
    {
      printf ("Hello World!\n");
      sleep (1);
    }
}
