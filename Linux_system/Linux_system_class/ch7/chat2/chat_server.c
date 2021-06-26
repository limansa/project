/* Server*/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "helper.h"
int main()
{ 
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	
	pthread_t send_thread;
	pthread_t recv_thread;

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
	while(1) {
		char ch[] = "ByeBye";
		char buf[128];
		char c;
		int i = 0;
		int res;

		printf("server waiting\n");
		/* Accept a connection. */
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,
		(struct sockaddr *)&client_address, &client_len);
		/* We can now read/write to client on client_sockfd. */

	//	res = read(client_sockfd, buf, 128);
		#if 1
                pthread_create( &send_thread, NULL, recv_msg,(void*) & client_sockfd);
                pthread_create( &recv_thread, NULL, send_msg,(void*) & client_sockfd);

	 	pthread_join(send_thread, NULL);
	        pthread_join(recv_thread, NULL);

		#else 
                while (1) {
                 recv_msg(client_sockfd);
	         send_msg(client_sockfd);
                }
		#endif
		write(client_sockfd, &ch, strlen(ch)+1);
		close(client_sockfd);
	}
}


