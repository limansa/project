/* After the #includes, the function prototypes and the global variable, we come to the
 main function. There the semaphore is created with a call to semget, which returns the
 semaphore ID. If the program is the first to be called (i.e. it's called with a parameter
 and argc > 1), a call is made to set_semvalue to initialize the semaphore and op_char is
 set to X. */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
        int val;                    /* value for SETVAL */
        struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
        unsigned short int *array;  /* array for GETALL, SETALL */
        struct seminfo *__buf;      /* buffer for IPC_INFO */
  };

typedef struct _semaphore{
       
	    int sem_id;
		int value;

}Semaphore;

int set_semvalue(Semaphore *sem);
void del_semvalue(Semaphore *sem);
int semaphore_p(Semaphore *sem);
 int semaphore_v(Semaphore *sem);

int init_semaphore(Semaphore * sem, key_t key,int init_value);



int init_semaphore(Semaphore * sem, key_t key,int init_value)
{	
    
    sem->sem_id = semget((key_t)0x1234, 1, 0666 | IPC_CREAT);
    sem->value=init_value;
   if (sem->sem_id<0)  return -1;

           if (!set_semvalue(sem)) {
            fprintf(stderr, "Failed to initialize semaphore\n");
           return -1;
             }
       
       
}


int set_semvalue(Semaphore *sem)
{
    union semun sem_union;

    sem_union.val = sem->value;
    if (semctl(sem->sem_id, 0, SETVAL, sem_union) == -1) return(0);
    return(1);
}

/* The del_semvalue function has almost the same form, except the call to semctl uses
 the command IPC_RMID to remove the semaphore's ID. */

 void del_semvalue(Semaphore *sem)
{
    union semun sem_union;
    
    if (semctl(sem->sem_id, 0, IPC_RMID, sem_union) == -1)
        fprintf(stderr, "Failed to delete semaphore\n");
}

/* semaphore_p changes the semaphore by -1 (waiting). */

 int semaphore_p(Semaphore *sem)
{
    struct sembuf sem_b;
    
    sem_b.sem_num = 0;
    sem_b.sem_op = -1; /* P() */
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem->sem_id, &sem_b, 1) == -1) {
        fprintf(stderr, "semaphore_p failed\n");
        return(0);
    }
    return(1);
}

/* semaphore_v is similar except for setting the sem_op part of the sembuf structure to 1,
 so that the semaphore becomes available. */

 int semaphore_v(Semaphore *sem)
{
    struct sembuf sem_b;
    
    sem_b.sem_num = 0;
    sem_b.sem_op = 1; /* V() */
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem->sem_id, &sem_b, 1) == -1) {
        fprintf(stderr, "semaphore_v failed\n");
        return(0);
    }
    return(1);
}

