

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

unsigned long copy_file(int from_fd,int to_fd);

unsigned long copy_file(int from_fd,int to_fd)
{
   int bytesread, byteswritten;
   int totalbytes=0;
   int unit_byte=100;
   int count;
   char buf[512];
   char *bp;   
   
   while (bytesread = read(from_fd, buf, unit_byte)) {
      if ((bytesread == -1) && (errno != EINTR))
         break;          /* real error occurred on the descriptor */
 
           printf("#");
           if((++count%30)==0) printf("\n");
           bp = buf;
         while(byteswritten = write(to_fd, bp, bytesread)) {
             if ((byteswritten == -1) && (errno != EINTR))
                break;
               
            if (byteswritten > 0) {
                bp += byteswritten;
                bytesread -= byteswritten;
                totalbytes+=byteswritten;
             }
         }
      
   }     
   printf("\n");
   return totalbytes;
}   
