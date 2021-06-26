/*
 * msgq.h -- JOSEPH Message Queue Routines
 *
 * Copyright 1998, John E. Stone
 *                 j.stone@acm.org
 *                 johns@cs.umr.edu
 *
 * $Id: msgq.h,v 1.6 1998/02/18 02:19:19 johns Exp $
 *
 */

#define JOSEPHQ_OUT     1
#define JOSEPHQ_IN      2

#define QNAME_OUT "/JOSEPHdout"
#define QNAME_IN  "/JOSEPHdin"

#define QNUM_OUT 451
#define QNUM_IN  452

#define JOSEPH_PRIORITY_NORMAL 1
#define JOSEPH_PRIORITY_HIGH   2

typedef void * QHandle;

QHandle JOSEPHq_create(int);
QHandle JOSEPHq_open(int);
int JOSEPHq_read(QHandle, JOSEPHIOEvent *);
int JOSEPHq_write(QHandle, JOSEPHIOEvent *, int);
void JOSEPHq_set_nonblock(QHandle);
void JOSEPHq_close(QHandle);
void JOSEPHq_delete(QHandle, int);



/* SYSV Message Queues */
typedef struct {
  int key;
  int q;
  int nonblock;
} msgqueue;

