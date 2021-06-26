#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#define QUIT "quit"

void * handle_key(void *);
void * handle_mice(void *);

typedef void * (*HANDLER)(void *);

#define MYJOBS 2
#define USE_THREAD

int main(void) {
 
 int i,ret;
 int  n_child=MYJOBS;
 pid_t childpid;

 
 pthread_t tid[MYJOBS];
 HANDLER do_job[MYJOBS]={handle_key,handle_mice};
  
  for (i = 0; i < n_child; i++) {
#ifdef USE_THREAD
	
	ret = pthread_create(&tid[i], NULL, do_job[i],0);
        if (ret!=0) {
          fprintf(stderr, "Failed to create thread\n");
           exit (-1);	  
	};


#else
	if ((childpid = fork())==0) {
	 fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld ..\n",
	  i, (long)getpid(), (long)getppid(), (long)childpid);
	   do_job[i](NULL);
	   break;
       }
#endif
 }

  while(1);

    return 0;
}


void * handle_key(void * arg) 
{

    char tmp[128];
    int n;
   fprintf(stderr,"%s ...\n",__func__);
   while(1) {
       if ((n=read(0,tmp,sizeof(tmp)))>0) {
               tmp[n-1]='\0';
               fprintf(stderr,"%s\n",tmp);
              if (!strcmp(tmp,QUIT)) {
                       fprintf(stderr,"bye bye\n");
                       break;
            }
        }
   }
  return (void *)0;
}

void * handle_mice(void * arg)
{
 
    
     int mice_fd;
    char buf[3];
     /*open mouse device*/
   fprintf(stderr,"%s ...\n",__func__);
    mice_fd = open("/dev/input/mice", O_RDONLY);
    if(!mice_fd)
    {
        printf("Failed to open \"/dev/input/mice\"\n");
        return (void *)0;
    }

  while(1) {
     if(read(mice_fd, buf, 3) <= 0) {
                continue;
        }
      printf("Button type = %d, X = %d, Y = %d\n", (buf[0] & 0x07), buf[1], buf[2]);

  }
    close(mice_fd);
   return (void *)0;

}










