/* Client */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "helper.h"

int main(int argc, char**argv)
{
	int client_sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char ch[] = "Hi !";
	char buf[128];

	
        pthread_t send_thread;
        pthread_t recv_thread;

   if (argc!=2) {
	    printf("Usage: %s <ip>\n",argv[0]);
        return 1;
	}




	/* Create a socket for the client. */
	client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	/* Name the socket, as agreed with the server. */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(argv[1]); //
//	address.sin_addr.s_addr = inet_addr("192.168.1.146"); //

	address.sin_port = htons(9733);
	len = sizeof(address);
	/* Now connect our socket to the server's socket. */
	result = connect(client_sockfd, (struct sockaddr *)&address, len);
	if(result == -1) {
		perror("oops: client2");
		exit(1);
	}
	/* We can now read/write via sockfd. */
	//int res ;
	//res = write(sockfd, &ch, strlen(ch)+1);
	//printf("res = %d\n",res);
	
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


	close(client_sockfd);
	exit(0);
}



