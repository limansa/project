#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define BLKSIZE 1024
unsigned int copy_file(int *fd);
 
int main(int argc, char *argv[])
{
   int file_fd[2];
      int totalbytes=0;
      int p;
  
 
   if (argc != 3) {
      fprintf(stderr, "Usage: %s from_file to_file\n", argv[0]);
      exit(1);
   }
 
   if ((file_fd[0] = open(argv[1], O_RDONLY)) == -1) {
      fprintf(stderr, "Could not open %s: %s\n",
              (char *) argv[1], (char *)strerror(errno));
      exit(1);
   }


  if ((file_fd[1] = open(argv[2], O_WRONLY | O_CREAT | O_EXCL,
              S_IRUSR | S_IWUSR)) == -1) {
      fprintf(stderr, "Could not create %s: %s\n",
              (char *) argv[2],(char *) strerror(errno));
      exit(1);
   }   
  printf("%d\n",file_fd[0]);
  printf("%d\n",file_fd[1]);
     p=copy_file(file_fd);
   printf("[%d] bytes copied\n",p);
 
      return 0;
}
unsigned int  copy_file(int *fd)
{
   int bytesread, byteswritten;
   unsigned int totalbytes=0;
   char buf[BLKSIZE];
    int from_fd, to_fd;
   char *bp;
   
 

   while (bytesread = read(from_fd, buf, BLKSIZE)) {
      if ((bytesread == -1) && (errno != EINTR))
         break;          /* real error occurred on the descriptor */
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

   close(from_fd);
   close(to_fd);
     return totalbytes;
}   
