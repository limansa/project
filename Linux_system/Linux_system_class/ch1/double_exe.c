#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
const char *lock_file = "exclusive.pid";

int main() {
    int file_desc;
    
    char buf[8];
        file_desc = open(lock_file, O_RDWR);
        if (file_desc == -1) { // only once
              
            printf("%d\n", getpid());
            sprintf(buf,"%ld", getpid());
            file_desc = open(lock_file, O_RDWR | O_CREAT | O_EXCL, 0444);
            write(file_desc,buf,strlen(buf));
             (void)close(file_desc);

 
           
        } else {
              
              read(file_desc,buf,8);
               (void)close(file_desc);
	       	
              buf[5]=0;
              
              printf("process [%s] is alreay running \n",buf,getpid());
              exit (-1);
               
        }


       
                /* critical region */

            sleep(10);            
            (void)unlink(lock_file);
                /* non-critical region */
    
exit(EXIT_SUCCESS);
}
