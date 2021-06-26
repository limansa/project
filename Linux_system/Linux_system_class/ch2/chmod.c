
















#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
  int fd,r;
  fd=open("./2-1.c",O_WRONLY);
 
  if (fd<0)  { printf("open error!\n"); return 0; }
  r=fchmod(fd,0755);
   if (r<0)
	  perror("My:");


 return 0;
}
	
