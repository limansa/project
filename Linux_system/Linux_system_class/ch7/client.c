/* Client */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define BLKSIZE 256

int make_socket(char *ip_addr, unsigned short port);
unsigned long copy_file(int from_fd,int to_fd);

unsigned long 
copy_file(int from_fd,int to_fd)
{
   	int bytesread, byteswritten;
   	int totalbytes=0;
   	char buf[512];
   	char *bp;

   	while ((bytesread = read(from_fd, buf, BLKSIZE))) 
	{
    	if ((bytesread == -1) && (errno != EINTR))
		{
         	break;          /* real error occurred on the descriptor */
		}
		bp = buf;
        while((byteswritten = write(to_fd, bp, bytesread))) 
		{
        	if ((byteswritten == -1) && (errno != EINTR))
            {
				break;
			}
            if (byteswritten > 0) 
			{
            	bp += byteswritten;
                bytesread -= byteswritten;
                totalbytes+=byteswritten;
            }
     	}
  	}
	return totalbytes;
}


int 
make_socket(char *ip_addr, unsigned short port)
{
	int socketfd = socket(AF_INET, SOCK_STREAM, 0);

	if(socketfd == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
	struct sockaddr_in saddr;
	int slen = sizeof(saddr);

	saddr.sin_family = AF_INET;
	if(ip_addr == NULL)
	{
		printf("Invalid IP address!\n");
		exit(1);
	}
	else
	{
		saddr.sin_addr.s_addr = inet_addr(ip_addr);
	}
	saddr.sin_port = htons(port);

 	if((connect(socketfd, (struct sockaddr *) &saddr, slen)) == -1)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}
	return socketfd;
}



int 
main()
{
	int sockfd,filefd;
	int flen;
//	char r_buffer[256] = {0};
	if((sockfd =make_socket("127.0.0.1",9734)) == -1) 
	{
		perror("oops: client2");
		exit(1);
	}
	if((filefd = open("1.jpg",O_RDONLY)) <0)
	{
		perror("open");
		exit(EXIT_FAILURE);	
	}
	printf("Start Trans\n");

	flen = copy_file(filefd, sockfd);
	printf("%d byte sent\n", flen);
//	read(sockfd, r_buffer, 256);
//	printf("Message from server = %s\n", r_buffer);
	close(sockfd);
	close(filefd);
	exit(0);
}
