#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define QUIT "quit"
#define POLLTIME 5

int main(void) {
    fd_set rfds;
    int mice_fd;
    struct timeval tv;
    int retval;


    
     /*open mouse device*/
    mice_fd = open("/dev/input/mice", O_RDONLY);
    if(!mice_fd)
    {
        printf("Failed to open \"/dev/input/mice\"\n");
        return -1;
    }

    
    /* Watch stdin (fd 0) to see when it has input. */
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    FD_SET(mice_fd, &rfds);
   
    /* Wait up to five seconds. */
    tv.tv_sec = POLLTIME;
    tv.tv_usec = 0;




  while (1) {
  
   retval = select(mice_fd+1, &rfds, NULL, NULL, &tv);
    /* Don't rely on the value of tv now! */
    if (retval == -1)
        perror("select()");
    else if (retval) {
      //  printf("Data is available now.\n");
        if (FD_ISSET(0, &rfds)) {
	  char tmp[128];
	  int n;
          if ((n=read(0,tmp,sizeof(tmp)))>0)
		tmp[n-1]='\0';
		fprintf(stderr,"%s\n",tmp);    
		if (!strcmp(tmp,QUIT)) {
			fprintf(stderr,"bye bye\n");    
			break;
		 }
          } else if (FD_ISSET(mice_fd, &rfds)) {

            // printf("detect mouse movement.\n");
                 char buf[3];
                 if(read(mice_fd, buf, 3) <= 0) {		
			continue; 
		   } 

       if (buf[0] & 0x1) printf("Left  button pressed,");
       if (buf[0] & 0x2) printf("Right button pressed,");
	   if (buf[0] & 0x4) printf("Middle button pressed,");

		printf("X = %d, Y = %d\n", (int)buf[1], buf[2]);	 	

          
            
	}
	

    } else
        printf("No data within %d seconds.\n",POLLTIME);

   /*select again*/
    tv.tv_sec = POLLTIME;
    tv.tv_usec = 0;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    FD_SET(mice_fd, &rfds);

   }

   close(mice_fd);

    return 0;
}

