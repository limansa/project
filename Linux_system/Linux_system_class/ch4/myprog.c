#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#define PIDFILE  "/var/myprog"


int main(int argc, char**argv) 
{
    int file_desc;
   

        char buf[10];  
	memset(buf,0,10);
	pid_t pid=getpid();
        file_desc = open(PIDFILE, O_RDWR | O_CREAT | O_EXCL, 0444);
        if (file_desc == -1) {
            read(file_desc,buf,10); 

            printf("[%s is already running (%s)! Exit]\n",argv[0],buf);
            exit (-1);
        }
        fprintf(stderr,"%d\n",pid);
        sprintf(buf,"%d",pid);
	write(file_desc,buf,strlen(buf));


		   
            sleep(10);
		    
            close(file_desc);
            unlink(PIDFILE);
                /* non-critical region */
   
    return 0;
}
