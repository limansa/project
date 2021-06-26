
 /*i2cdetect.c - a user-space program to scan for I2C devices 
 Copyright (C) 1999-2004  Frodo Looijaard <frodol@dds.nl>, and ark D. Studebaker <mdsxyz123@yahoo.com>
    Copyright (C) 2004-2010  Jean Delvare <khali@linux-fr.org>*/
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#define QUIT "quit"
#define POLLTIME 5

int main(void) {
    fd_set rfds;
    struct timeval tv;
    int retval;
    /* Watch stdin (fd 0) to see when it has input. */
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    /* Wait up to five seconds. */
    tv.tv_sec = POLLTIME;
    tv.tv_usec = 0;
  while (1) {
  
   retval = select(1, &rfds, NULL, NULL, &tv);
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
            }	

    } else
        printf("No data within %d seconds.\n",POLLTIME);

   /*select again*/
    tv.tv_sec = POLLTIME;
    tv.tv_usec = 0;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

   }



    return 0;
}

