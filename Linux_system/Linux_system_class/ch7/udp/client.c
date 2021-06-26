/* Client */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char buffer[10] = "Hi!!";
/* Create a socket for the client. */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
/* Name the socket, as agreed with the server. */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("192.168.1.117");
	address.sin_port = htons(9734);
	len = sizeof(address);

	sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&address, len);
	bzero(buffer, sizeof(buffer));
	result = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&address, &len);
	buffer[result] = '\0';
	printf("read server %d bytes:%s\n",result,buffer);
	close(sockfd);
	exit(0);
}
