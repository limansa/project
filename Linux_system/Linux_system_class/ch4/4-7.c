#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main (int argc, char **argv) 
{
  pid_t pid;
  int exit_code;
  int i,n;


   if (argc != 2) {
        fprintf(stderr, "Usage: %s processes\n", argv[0]);
        return 1;
   }
    n = atoi(argv[1]);

   for (i = 1; i < n; i++)
      if ((pid = fork())==0)
           break;
  
  switch (pid)
    
    {
    case -1:
      exit (1);
    case 0:
      printf ("Child PID %d\n", getpid ());
      exit_code = 37;
      break;
    default:
      printf ("Parent PID %d\n", getpid ());
      exit_code = 0;
      break;
    }
  
/* This section of the program waits for the child process to finish. */ 
    if (pid)
    {				// parent
      sleep (10);
      int stat_val;
      pid_t child_pid;
      while ((child_pid = wait (&stat_val)) > 0)
	{
	  printf ("Child has finished: PID = %d\n", child_pid);
	  if (WIFEXITED (stat_val))
	    {
	      printf ("Child exited with code %d\n", WEXITSTATUS (stat_val));
	    }
	}
    }
  else
    {
      sleep (2);
       fprintf(stderr, "Child terminate --> i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
         i, (long)getpid(), (long)getppid(), (long)pid);

      return exit_code;
    }

	return 0;
}
