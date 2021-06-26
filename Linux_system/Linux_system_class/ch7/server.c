/* Server*/
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>


#define QUEUE_LEN 5
#define BLKSIZE 256

int make_listen_socket(char *ip_addr, unsigned short port);
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
			printf("!!!\n");
			break;          /* real error occurred on the descriptor */
		}
        bp = buf;
        while((byteswritten = write(to_fd, bp, bytesread))) 
		{
        	if ((byteswritten == -1) && (errno != EINTR))
            	break;

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
make_listen_socket(char *ip_addr, unsigned short port)
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
		saddr.sin_addr.s_addr = INADDR_ANY;
	}
	else
	{
		saddr.sin_addr.s_addr = inet_addr(ip_addr);
	}
	saddr.sin_port = htons(port);

	if(bind(socketfd, (struct sockaddr *) &saddr, slen) == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if(listen(socketfd, QUEUE_LEN) == -1)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	return socketfd;
}

int 
main()
{ 
	int server_sockfd, client_sockfd;
	int filefd;
	int flen;
	unsigned int client_len;
	struct sockaddr_in client_address;
	char s_buffer[256] = "I Got File.";

	server_sockfd = make_listen_socket(NULL, 9734);
	filefd = open("2.jpg", O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR|S_IROTH);	
	if(filefd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	while(1) 
	{
		printf("server waiting\n");
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,
			(struct sockaddr *)&client_address, &client_len);
		flen = copy_file(client_sockfd, filefd);
		printf("Recive From Client : %s:%d\n", 
			inet_ntoa(client_address.sin_addr),
			ntohs(client_address.sin_port));
		printf("%d Bytes Recive\n", flen);
		write(client_sockfd, s_buffer, strlen(s_buffer));
		close(client_sockfd);
	}
	close(filefd);
}
