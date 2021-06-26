       #include <sys/wait.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <stdio.h>
       void test1 (int sig) {
        
          printf("%s called\n",__func__);

        }

       void test2 (int sig) {

          printf("%s called\n",__func__);

        }

         void test3 (int sig) {

          printf("%s called\n",__func__);

        }



       int
       main(int argc, char *argv[])
       {
           pid_t cpid, w;
           int status;
           signal(SIGINT,test1);
           signal(SIGSTOP,test2);
           signal(SIGCONT,test3);
           cpid = fork();
           if (cpid == -1) { perror("fork"); exit(EXIT_FAILURE); }

           if (cpid == 0) {            /* Code executed by child */
               printf("Child PID is %ld\n", (long) getpid());
               if (argc == 1)
                   pause();                    /* Wait for signals */
                  
               _exit(atoi(argv[1]));

           } else {                    /* Code executed by parent */
               do {
		  printf("Parent PID is %ld. and call wait()...\n", (long) getpid());
                   //w = waitpid(cpid, &status, WUNTRACED | WCONTINUED | WSTOPPED);
                   wait(NULL);
                   //w = waitpid(cpid, &status, WUNTRACED | WCONTINUED | WSTOPPED);
                   if (w == -1) { perror("waitpid"); exit(EXIT_FAILURE); }

                   if (WIFEXITED(status)) {
                       printf("exited, status=%d\n", WEXITSTATUS(status));
                   } else if (WIFSIGNALED(status)) {
                       printf("killed by signal %d\n", WTERMSIG(status));
                   } else if (WIFSTOPPED(status)) {
                       printf("stopped by signal %d\n", WSTOPSIG(status));
                   } else if (WIFCONTINUED(status)) {
                       printf("continued\n");
                   }
               } while (!WIFEXITED(status) && !WIFSIGNALED(status));
               exit(EXIT_SUCCESS);
           }
       }

