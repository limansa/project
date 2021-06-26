#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>
#include<time.h>

int fd = 0;
int accept_flag = 0;
int buf[30] ;
char dev_name[] = "/dev/mydevice";

void signal_handler(int num);

int main(int argc,char *argv[]){

       int pid;

	// setup this process that 
	// if accept a signal: SIGIO
	// call func: signal_handler()
	signal(SIGIO, signal_handler);


	fd = open(dev_name ,O_RDONLY);
	if(fd <= 0) {
           fprintf(stderr,"Error: cannot open %s \n",dev_name);
          return -1;

       }

        pid= getpid();
        printf("process with pid %d START!\n", pid);


	fcntl(fd, F_SETOWN, getpid());
	fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | FASYNC);

	printf("process open device %s with fd: %d\n", dev_name , fd);

	while(!accept_flag){
		printf("Nothing to do ... Sleeping ... ZZZzzz....\n");
		usleep(1000000);
	}

	printf("I accepted something...and work done!\n");
	printf("Now the process would exit....\n");
	close(fd);
	return 0;
}

void signal_handler(int num){
	printf("accept signal which means the data ready for read:\n");
	printf("So, I read it !\n");
	int len = read(fd, buf, 30);
	buf[5] = '\0';
	printf("msg with len : %d\n", len);
	printf("I accept : %s\n", buf);
	while(len--) buf[len] = '\0';
	accept_flag = 1;
}
