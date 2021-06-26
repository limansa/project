
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
int main()
{
  char *p;
  char buf[128];
  p=(char *)getcwd(buf,128);
   if (!p)
	  perror("My:");

  printf("getcwd=%s\n",buf);
  
  chdir("/home");

   p=(char *)getcwd(buf,128);
   printf("getcwd=%s\n",buf);

 return 0;
}
	
