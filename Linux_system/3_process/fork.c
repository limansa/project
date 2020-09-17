#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void print_pid_ppid()
{
    printf("PPID=%ld PID=%ld\n", (long)getppid(), (long)getpid());
    return;
}

int main (void)
{
    printf("+++++++\n");
    printf("Start: ");
    print_pid_ppid();
    int i = 0;
    int fork_ret = -1;
    int fork_ret_2 = -2;
    fork_ret = fork();
    fork_ret_2 = fork();

    for (i=0; i < 10; i++) {
        printf("fork_ret=%d %d The %d times\n", fork_ret, fork_ret_2, i+1);
        if (fork_ret == 0) {
            printf("Child process: ");
            print_pid_ppid();
        } else if (fork_ret > 0) {
            printf("Parent process: ");
            print_pid_ppid();
        } else {
            printf("fork failed\n");
        }
        sleep(1);
    }
    printf("--------\n");
    return 0;
}

