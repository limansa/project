/* 
 * msgsnd.c -- Simple lamo test program for the message queue code.
 *
 * $Id: msgsnd.c,v 1.5 1998/01/26 01:07:28 johns Exp $
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "seq.h"
#include "msgq.h"

JOSEPHIOEvent ev;

int main() {
  QHandle q;

  printf("message queuing sender demo.\n");

  if ((q = JOSEPHq_open()) == NULL) {
    return -1;
  }

  while(1) {
    int msg[4];
    int i;

    printf("enter message: ");
    fflush(stdout);
    scanf("%x %x %x", &msg[0], &msg[1], &msg[2]); 
    scanf("%d", &ev.msglen);

    for (i=0; i<4; i++)
     ev.msg[i] = msg[i];

    ev.delay.tv_sec = 1;
    ev.delay.tv_nsec = 1000;
 
    if (JOSEPHq_write(q, &ev, JOSEPH_PRIORITY_HIGH) == -1)
      printf("error sending message!\n");

    if (ev.msglen < 0) 
      break;
  }

  JOSEPHq_close(q);

  return 0;
}

