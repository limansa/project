/* Server*/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "tcputils.h"

int main()
{ 
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
       
      server_sockfd=open_sock(9735);

	while(1) {
		unsigned char ch[] = "ByeBye";
		unsigned char buf[128];
		 char c;
		int i = 0;
		int res;

		printf("server waiting\n");
		/* Accept a connection. */
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,
		(struct sockaddr *)&client_address, &client_len);
		/* We can now read/write to client on client_sockfd. */
               
		res = read_sock(client_sockfd, buf, 128);
		
		printf("res = %d\n",res);
                if (res==0) {
		printf("char from client %s\n", buf);
                }
		write_sock(client_sockfd, ch, strlen(ch)+1);
		close_sock(client_sockfd);
	}
	 close(server_sockfd);
}
