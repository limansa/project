/*
* rdfifo.c - Create a FIFO and read from it
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#define FIFO_NAME "fifo1"
int main(void)
{
	int fd; /* Descriptor for FIFO */
	int len; /* Bytes read from FIFO */
	char buf[PIPE_BUF];
	mode_t mode = 0777;
	int res;
	#if 0
	if (access(FIFO_NAME, F_OK) == -1) {
	res = mkfifo(FIFO_NAME, mode);
	if (res != 0) {
	fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
	exit(EXIT_FAILURE);
	}
	}
	#endif
	/* Open the FIFO read-only */
	if((fd = open(FIFO_NAME , O_RDONLY)) < 0) {
	perror("open");
	exit(EXIT_FAILURE);
	}
	/* Read and display the FIFO's output until EOF */
	while((len = read(fd, buf, PIPE_BUF - 1)) > 0)
		printf("rdfifo read: %s", buf);
	
	close(fd);
	exit(EXIT_SUCCESS);
}
