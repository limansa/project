#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>

char on[2] = "1";
char off[2] = "0";
int count = 100;

int main(int argc,char *argv[]){
	int led0 = open("/dev/myLED0",O_RDWR);
	int led1 = open("/dev/myLED1",O_RDWR);
         

        if (led0 < 0 || led1 < 0) {
          fprintf(stderr,"cannot open device\n");
          return -1;
         }
	while(count--){
	printf("%d: LEDs are blinking....\n",count);

#if 0
         ioctl(led0,0,0);
         ioctl(led1,1,1);
         usleep(100000);
         ioctl(led0,0,1);
         ioctl(led1,1,0);
         usleep(100000);


#else

		write(led0,on,2); 
		write(led1,off,2);

		usleep(500000);

		write(led0,off,2); 
		write(led1,on,2);

		usleep(500000);

#endif
	}

	write(led0,off,2);
	write(led1,off,2);

	close(led0);
	close(led1);
	return 0;
}
