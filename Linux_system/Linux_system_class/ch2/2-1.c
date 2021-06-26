


#include <sys/types.h>
#include <sys/stat.h>

int main()
{
  int r;
  r=chmod("./2-1.c",0777);
   if (r<0)
	  perror("My:");


 return 0;
}
	
