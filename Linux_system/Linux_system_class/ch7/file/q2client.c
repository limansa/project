/* Client */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<fcntl.h>

#define FILENAME "test.jpg"

int main()
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char buf[128];
	int fd;
	int size;


	/* Create a socket for the client. */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	/* Name the socket, as agreed with the server. */
	address.sin_family = AF_INET;
	//127.0.0.1
	//192.168.1.150
	//192.168.1.142
	address.sin_addr.s_addr = inet_addr("127.0.0.1"); //
	address.sin_port = htons(9741);
	len = sizeof(address);
	/* Now connect our socket to the server's socket. */
	result = connect(sockfd, (struct sockaddr *)&address, len);
	if(result == -1) {
		perror("oops: client2");
		exit(1);
	}
	/* We can now read/write via sockfd. */

	size = 0;
	fd = open(FILENAME,O_RDONLY);
	if (fd < 0) {
 	   perror("client:");
	  
	}

	size=copy_file (fd,sockfd);


	if( size > 0 ){
		printf("write size = %d\n", size);
	}
	else{
		perror("size");
	}

	close(fd);
	close(sockfd);
	exit(0);
}
