#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void) {
   char c[80];
   int myfd;
   int num_read=0;
  
   if ((myfd = open("my.dat", O_RDWR )) == -1) {
      perror("Failed to open file");
      return 1;
   }
  	
    while((num_read=read(myfd, &c,2))>0) {
//      printf("Process %ld got %d byted %c\n", (long)getpid(), num_read,c);
	//printf("\n\n");
        write(1, c, 2); 
    } 
       
   return 0;
}
