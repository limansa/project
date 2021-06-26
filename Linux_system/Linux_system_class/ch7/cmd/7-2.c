/* Server*/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "msg.h"

int main()
{ 
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
        struct msg_control control;
        struct msg_report  report;
	/* Create an unnamed socket for the server. */
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	/* Name the socket. */
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(9735);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
	/* Create a connection queue and wait for clients. */
	listen(server_sockfd, 5);
    
        /*initialize data*/
          memset(&control,0,sizeof(struct msg_control));
          memset(&report,0,sizeof(struct msg_report));





	while(1) {
	
		int res;
                    
		printf("server waiting\n");
		/* Accept a connection. */
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,
		(struct sockaddr *)&client_address, &client_len);
		/* We can now read/write to client on client_sockfd. */

		res = read(client_sockfd,&control,sizeof(struct msg_control));
		 
                report.status=OK; 
		printf("cmd => %d\n",control.cmd);
                 
		write(client_sockfd, &report,sizeof(struct msg_report));
		close(client_sockfd);
	}
}
