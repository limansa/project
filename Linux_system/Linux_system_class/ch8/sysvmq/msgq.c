/*
 * msgq.c -- Message Queueing Routines
 *
 * Copyright 1998, John E. Stone
 *                 j.stone@acm.org
 *                 johns@cs.umr.edu
 *
 * $Id: msgq.c,v 1.12 1998/02/18 02:19:19 johns Exp $
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <errno.h>
#include <sys/errno.h>
#include "seq.h"

#define MSGQ_PRIVATE
#include "msgq.h"

#ifndef MSG_R 
#define MSG_R 0400
#endif
#ifndef MSG_W 
#define MSG_W 0200
#endif

static int JOSEPHqnum(int msgqtype) {
  switch(msgqtype) {
    case JOSEPHQ_OUT :
      return QNUM_OUT;
    case JOSEPHQ_IN : 
      return QNUM_IN;
  }
  return 0;
}

QHandle JOSEPHq_create(int msgqtype) {
  msgqueue * q;
  int qnum;

  qnum = JOSEPHqnum(msgqtype);
  if (qnum == 0) 
    return NULL;

  if ((q = (msgqueue *) malloc(sizeof(msgqueue))) == NULL)
    return NULL;

  q->q = msgget(qnum, (MSG_R | MSG_W) | 
                      ((MSG_R | MSG_W) >> 3) | 
                      ((MSG_R | MSG_W) >> 6) |
                      IPC_CREAT );
  
  if (q->q == -1) {
    free(q);
    return NULL;
  } 

  return q;
}

QHandle JOSEPHq_open(int msgqtype) {
  msgqueue * q;
  int qnum;

  qnum = JOSEPHqnum(msgqtype);
  if (qnum == 0) 
    return NULL;

  if ((q = (msgqueue *) malloc(sizeof(msgqueue))) == NULL)
    return NULL;

  q->q = msgget(qnum, (MSG_R | MSG_W) | 
                      ((MSG_R | MSG_W) >> 3) | 
                      ((MSG_R | MSG_W) >> 6) );
  
  if (q->q == -1) {
    free(q);
    return NULL;
  } 

  q->nonblock = 0;

  return q;
}


int JOSEPHq_read(QHandle voidhandle, JOSEPHIOEvent * ev) {
  msgqueue * q = voidhandle; 
  JOSEPHIOEvent newev;
  int rc;

  /* XXX: Weird stuff happens when we receive right into ev */
  /*      Something seems to be wrong with the calculation of sizeof */
  /*      probably need to use lint on this code a bit */

  rc = msgrcv(q->q, (void *) &newev, sizeof(JOSEPHIOEvent), 0, q->nonblock); 
  *ev = newev;
  return rc;
}

int JOSEPHq_write(QHandle voidhandle, JOSEPHIOEvent * ev, int priority) {
  msgqueue * q = voidhandle; 
  int rc;

  ev->mtype = priority;
  rc = msgsnd(q->q, (void *) ev, sizeof(JOSEPHIOEvent), 0); 
  while ((rc == -1) && (errno == EINTR)) { 
    rc = msgsnd(q->q, (void *) ev, sizeof(JOSEPHIOEvent), 0); 
  }

  return rc;
}

void JOSEPHq_set_nonblock(QHandle voidhandle) {
  msgqueue * q = voidhandle;
  q->nonblock = IPC_NOWAIT;  
}

void JOSEPHq_close(QHandle voidhandle) {
  msgqueue * q = voidhandle;
  free(q);
}

void JOSEPHq_delete(QHandle voidhandle, int msgqtype) {
  msgqueue * q = voidhandle;

  msgctl(q->q, IPC_RMID, NULL);
  free(q);
}


