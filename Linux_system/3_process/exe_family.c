#include <stdio.h>
#include <unistd.h>

void print_pid_ppid()
{
    printf("PID=%ld PPID=%ld\n", (long)getpid(), (long)getppid());
    return;
}

int main (void)
{
    printf("main: ");
    print_pid_ppid();
    system("ls -al");
    printf("1: ");
    print_pid_ppid();

    //The exec() family of functions replaces the current process image with a new process image.
    //So it won't print 2: print_pid_ppid function.
    execl("/bin/ls", "ls", "-l", 0);
    printf("2: ");
    print_pid_ppid();

    printf("Finish\n");
    return 0;
}

