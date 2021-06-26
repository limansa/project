/* Client */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char ch[] = "Hi !";
	char buf[128];

	/* Create a socket for the client. */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	/* Name the socket, as agreed with the server. */
	address.sin_family = AF_INET;
	//127.0.0.1
	//192.168.1.150
	//192.168.1.142
	address.sin_addr.s_addr = inet_addr("192.168.2.194"); //
	address.sin_port = htons(9735);
	len = sizeof(address);
	/* Now connect our socket to the server's socket. */
	result = connect(sockfd, (struct sockaddr *)&address, len);
	if(result == -1) {
		perror("oops: client2");
		exit(1);
	}
	/* We can now read/write via sockfd. */
	int res ;
	res = write(sockfd, &ch, strlen(ch)+1);
	//printf("res = %d\n",res);

	if( read(sockfd, buf, 128) > 0 ){
		printf("char from server = %s\n", buf);
	}
	else{
		perror("read");
	}
	close(sockfd);
	exit(0);
}
