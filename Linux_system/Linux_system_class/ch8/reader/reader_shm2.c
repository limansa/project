/* The second program is the producer and allows us to enter data for consumers.
 It's very similar to shm1.c and looks like this. */

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
    char buffer[BUFSIZ];
    int shmid;

    shmid = shmget((key_t)0x1234, sizeof(CardReader *), 0666 | IPC_CREAT);
    printf("shmid=%d\n",shmid);
    if (shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Memory attached at %X\n", (int)shared_memory);

    card_ptr = (CardReader *)shared_memory;
    while(running) {
        while(card_ptr->status == WAITID) {
            sleep(1);            
            printf("waiting for reader...\n");
        }

	if(card_ptr->status == READY){
                //strncpy(buffer, card_ptr->data , ID_SZ);
                printf("ID: %10s\n",card_ptr->data);
                //if(XXX) card_ptr->status == DONE;
		printf("shm2 outputed ID.\n");
		card_ptr->status = WAITID;
                
        }
	//if(card_ptr->status == DONE)
        //running = 0;
        
    }

    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
