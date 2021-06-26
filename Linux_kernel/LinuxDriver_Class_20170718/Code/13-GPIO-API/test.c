#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>

char on[2] = "1";
char off[2] = "0";
char buff[10];
int count = 10;


int main(int argc,char *argv[]){
	int led0 = open("/dev/myLED0",O_RDWR);
	int led1 = open("/dev/myLED1",O_RDWR);
	int res;

	while(count--){
		write(led0,on,2); 
		write(led1,off,2);
		usleep(500000);
		write(led0,off,2); 
		write(led1,on,2);
		usleep(500000);

		res = read(led0, buff,1);
		printf("led0: res: %d level: %d\n", res, buff[0]);
		res = read(led1, buff,1);
		printf("led1: res: %d level: %d\n", res, buff[0]);
	}

	printf("out of loop\n");
	write(led0,off,2);
	write(led1,off,2);

	printf("to close file\n");
	close(led0);
	close(led1);
	return 0;
}
