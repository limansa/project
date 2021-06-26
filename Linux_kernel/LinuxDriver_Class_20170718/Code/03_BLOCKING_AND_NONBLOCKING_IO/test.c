#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include <signal.h>



void handler(int sig);
 
int main(int argc,char *argv[]){

	int res = 0;


        char buff[10]={0};
        signal(SIGINT,handler);

	printf("==========================\n");
	printf("START to NON_BLOCK READ FILE\n");
	// non-blocking io read:
	int fd = open("/dev/myBR_file", O_RDONLY /*| O_NONBLOCK */);
	if(fd < 0){
		printf("can't open file myBR_file.\n");
	}else{
		res = read(fd,buff,10);
		if(res < 0){
		        perror("test:");
		}else{
			printf("### read function return: %s\n",buff);
		}
	}
	close(fd);
	printf("==========================\n");



	return 0;
}


void handler(int sig) 
{
	printf("catch SIGINT !\n");
	
}
