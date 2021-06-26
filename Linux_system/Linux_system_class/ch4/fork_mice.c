#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define QUIT "quit"

int handle_key();
int handle_mice();

typedef int (*HANDLER)(void);

#define MYJOBS 2

int main(void) {
 
 int i;
 int  n_child=MYJOBS;
 pid_t childpid;

 HANDLER do_job[MYJOBS]={handle_key,handle_mice};
  
  for (i = 0; i < n_child; i++) {
	if ((childpid = fork())==0) {
	 fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld ..\n",
	  i, (long)getpid(), (long)getppid(), (long)childpid);
	   do_job[i]();
	   break;
       }
 }

  while(1);

    return 0;
}


int handle_key() 
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
  return 0;
}

int handle_mice()
{
 
    
     int mice_fd;
    char buf[3];
     /*open mouse device*/
   fprintf(stderr,"%s ...\n",__func__);
    mice_fd = open("/dev/input/mice", O_RDONLY);
    if(!mice_fd)
    {
        printf("Failed to open \"/dev/input/mice\"\n");
        return -1;
    }

  while(1) {
     if(read(mice_fd, buf, 3) <= 0) {
                continue;
        }


      if (buf[0] & 0x1) printf("Left  button pressed,");
      if (buf[0] & 0x2) printf("Right button pressed,");
	  if (buf[0] & 0x4) printf("Middle button pressed,");
	  printf("dX = %d, dY = %d\n",buf[1], buf[2]);
	

  }
    close(mice_fd);
   return 0;

}










