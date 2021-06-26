/* Our first program is a consumer. After the headers the shared memory segment
 (the size of our shared memory structure) is created with a call to shmget,
 with the IPC_CREAT bit specified. */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "reader_com.h"

int main()
{
    int running = 1;
    void *shared_memory = (void *)0;
    CardReader *card_ptr;
    int shmid;

    srand((unsigned int)getpid());    

    shmid = shmget((key_t)0x1234, sizeof(CardReader *), 0666 | IPC_CREAT);
   
	printf("shmid=%d\n",shmid);
    if (shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

/* We now make the shared memory accessible to the program. */

    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Memory attached at %X\n", (int)shared_memory);

/* The next portion of the program assigns the shared_memory segment to shared_stuff,
 which then prints out any text in written_by_you. The loop continues until end is found
 in written_by_you. The call to sleep forces the consumer to sit in its critical section,
 which makes the producer wait. */
    char ID[11] = "0123456789";
    card_ptr = (CardReader *)shared_memory;
    card_ptr->status = WAITID;
    while(running) {
        if (card_ptr->status == WAITID) {
            printf("shm1 Waitting ID.\n\n");
            sleep( rand() % 6 ); /* make the other process wait for us ! */
	    //if(getID)
	        strcpy(card_ptr->data,ID);
		printf("shm1 got ID.\n\n");
		card_ptr->status = READY;
	}
	//if(card_ptr->status == DONE){
	    sleep(1);
	    card_ptr->status = WAITID;
                //running = 0;
		
        //}
    }

/* Lastly, the shared memory is detached and then deleted. */

    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

