#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define QUIT "quit"

int handle_key(int *pipe);
int handle_mice(int *pipe);

typedef int (*HANDLER)(int *pipe);

#define MYJOBS 2

int main(void) {
 
 int i;
 int  n_child=2;
 pid_t childpid;
 int key_pipe[2];
 int mice_pipe[2];
 int *data_pipe[2]={mice_pipe,key_pipe};
 HANDLER do_job[MYJOBS]={handle_mice,handle_key};
 int ret;
 char c; 
  for (i = 0; i < n_child; i++) {

	   if (pipe(data_pipe[i]) <0 ) perror("pipe:");

	if ((childpid = fork())==0) {
	 fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld ..\n",
	  i, (long)getpid(), (long)getppid(), (long)childpid);
	   do_job[i](data_pipe[i]);
	   break;
       }
 }

//  printf("key %d %d\n",key_pipe[0],key_pipe[1]);
//  printf("mice %d %d\n",mice_pipe[0],mice_pipe[1]);
  
  close(data_pipe[0][1]);
  close(data_pipe[1][1]);

 
  while  (ret=read(mice_pipe[0],&c,1)) {
	   if (ret<0) {
		   perror("read error");
		   break;
        }else
           printf("%d\n",c);

  }
  wait();
  wait();

    return 0;
}


int handle_key(int *pipe) 
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

int handle_mice(int *pipe)
{
 
    
     int mice_fd;
    char buf[3];
     /*open mouse device*/
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
      //printf("Button type = %d, X = %d, Y = %d\n", (buf[0] & 0x07), buf[1], buf[2]);
     
	  char ch=buf[0] & 0x7;
       if (ch!=0) 
	        if (write(pipe[1],&ch,1)<0) perror("mouse write:");

  }
    close(mice_fd);
   return 0;

}










