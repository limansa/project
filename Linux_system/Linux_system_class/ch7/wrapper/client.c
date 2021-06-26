/* Client */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "tcputils.h"
int main()
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	unsigned char ch[] = "Hi !";
	char buf[128];

	/* Create a socket for the client. */
	sockfd=open_clientsock("127.0.0.1",9735); //
	/* We can now read/write via sockfd. */
	int res ;
	
        res = write_sock(sockfd, ch, 128);
        if (res!=0) printf("has more data~~\n");	
       printf("res = %d\n",res);

	   res=read_sock(sockfd, buf, 128);
         
       printf("res = %d\n",res);
        if (res==0) { 	
            printf("char from server = %s\n", buf);
	}
	
	close_sock(sockfd);
	exit(0);
}
