#include     <stdio.h>      
#include     <stdlib.h>    
#include     <unistd.h>     
#include     <sys/types.h>  
#include     <sys/stat.h>   
#include     <fcntl.h>      
#include     <termios.h>    
#include     <errno.h>     
#include <string.h>
//#include <stdlib.h>
static char *serial_name[]={"/dev/ttyUSB0","/dev/ttyS1","/dev/ttySAC1","/dev/ttySAC2"};
int main(void)
{
	int  n, len,  fd_max,i;
  fd_set  readfds;
  char buffer[256];
	static struct termios oldtio,newtio;

	printf(" *** 0:ttyUSB0 ***\r\n,*** 1:ttyS1 ***\r\n,*** 2:ttySAC1 ***\r\n,*** 3:ttySAC2 ***\r\n");
	printf("*** please input the open serial : ");
	scanf("%d",&i);

	int fd = open(serial_name[i],O_RDWR | O_NOCTTY | O_NDELAY);//270
	if(fd<0){
		perror("Cannot Open Serial Port !\n");
	}
	else 
		printf("open Serial Port success !\r\n");
	
	tcgetattr(fd,&oldtio);
	tcgetattr(fd,&newtio);
	

	cfsetispeed(&newtio,B9600);
	cfsetospeed(&newtio,B9600);

	newtio.c_lflag&= ~(  ECHO | ECHOE | ISIG);
	//newtio.c_lflag&= ~(ICANON | ECHO | ECHOE | ISIG);
	
	newtio.c_cflag &= ~PARENB;
	
	
	newtio.c_cflag &= ~CSTOPB;
	

	newtio.c_cflag &= ~CSIZE;
	newtio.c_cflag |= CS8;
	

	newtio.c_oflag &= ~OPOST;
	

	newtio.c_cflag |= (CLOCAL | CREAD);
	
	newtio.c_iflag = 0;
	

	newtio.c_cc[VTIME] = 4;
	newtio.c_cc[VMIN] = 5;
	

	if(tcsetattr(fd,TCSAFLUSH,&newtio)<0)
	{
		printf("tcsetattr fail !\n");
		exit(1);
	}

    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    fd_max = fd + 1;
	
    /* Do the select */
    //return 0;
    while(1) 
    {
  	
	   n = select(fd_max,&readfds,NULL,NULL,NULL);
	   memset(buffer, 0, sizeof(buffer));
	   if (n<=0)
     	      printf("select failed");
     else
        {
            if (FD_ISSET(fd, &readfds))
                 {	  	char buf[16];
	 		              len=read(fd, buffer, 256);
			              buffer[len] ='\0';
        	              fprintf(stderr, "%s",buffer);  
        	          //    sprintf(buf, "got data:%s\n",buf);  
                  	    //  write(fd,buf,strlen(buf));
                	}
	      }
    }
}	
