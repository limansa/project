
#include <stdio.h>

#define DEBUG 3

#ifdef  DEBUG
#define debug(fmt,args...)      printf (fmt ,##args)
#define debugX(level,fmt,args...) if (DEBUG>=level) printf(fmt,##args);
#else
#define debug(fmt,args...)
#define debugX(level,fmt,args...)
#endif  /* DEBUG */


int main()
{

 int n=10;
 debug("bug found!!\n"); 
 debug("n is %d\n",n);
 
 debugX(3,"bug found!!\n");
 debugX(4,"n is %d\n",n);




 return 0;
}
