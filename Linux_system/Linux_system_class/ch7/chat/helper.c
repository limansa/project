

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

void * recv_msg(void * s)
{
 
 
 char buf[128];
 int n; 
while (1) { 
 n = read(*(int *)s, buf, 128);
  if (n<=0)
  {    fprintf(stderr,"read  error!!");
       return (void *)-1;
  }
 printf("\n\E[33m %s \E[0m\n",buf);

}
 return (void *) n;

}



void * send_msg(void *s)
{

  char buf[128];
  int n;
  int len;

 while (1) {
    printf("Input==>");
    fgets(buf,128,stdin);
    len=strlen(buf);
    n=write(*(int *)s,buf,len+1);
    if (n!=len+1 || n < 0) {
      fprintf(stderr,"write error!!");
      goto error;
     }

  } 

   return (void *)n;  


error:

   return NULL;

}

