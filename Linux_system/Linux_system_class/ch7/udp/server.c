/* UDP Server */ 
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{ 
	int sockfd;	
	int server_len, client_len,result;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	char buffer[128];
/* Create an unnamed socket for the server. */
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
/* Name the socket. */
	server_address.sin_family = AF_INET;
   server_address.sin_port = htons(9734);
   server_address.sin_addr.s_addr = INADDR_ANY;
   server_len = sizeof(server_address);
	bind(sockfd, (struct sockaddr *)&server_address, server_len);



/* Create a connection queue and wait for clients. */
	
	while(1) {
		bzero(buffer,sizeof(buffer));
		result = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_address, &client_len);	
		buffer[result] = '\0';
   	printf("read %d bytes from %s:%d : %s\n", result, inet_ntoa(client_address.sin_addr),ntohs(client_address.sin_port),buffer);
		sprintf(buffer,"bye-bye!!");
		sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_address, client_len);

		printf("server waiting\n");

	}
}
