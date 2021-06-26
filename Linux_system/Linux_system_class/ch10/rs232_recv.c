#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "conntty.h"

#define BAUDRATE B38400
#define	MODEMDEVICE "/dev/ttyUSB0"
#define _POSIX_SOURCE 1


void handle(char* n);
int main(void)
{
	int fd,n;
	struct termios  oldtio, newtio;
	int len=0;
	unsigned char rec[2];

	fd = com_init(fd,MODEMDEVICE,BAUDRATE,oldtio,newtio);
	while(1){
 			len = read(fd, rec,2);
			if(len>0)
				handle(rec);

  	}
  	com_close(fd,oldtio);
  	return 0;
}

void handle(char* n)
{
        int i;
  	char led_no,led_status,tmp;
	char cmd[64]="";

  	switch(n[0])
	{
		//LED
		case 0x00: 
			led_no = n[1]>>4; 
			tmp = n[1]<<4; 
			led_status = tmp>>4; 
			sprintf(cmd,"led %d %d",led_no,led_status);
			system(cmd);
			//printf("command:led %d %d\n",led_no,led_status);
			break;

		//REBOOT
		case 0x01:
			system("reboot");
			//printf("command:reboot\n");
			break;
		default:
			printf("nothing to do\n");
	}

}
