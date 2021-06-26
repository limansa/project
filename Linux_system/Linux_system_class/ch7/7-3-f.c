/* Client */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
unsigned long copy_file(int from_fd,int to_fd);
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
	address.sin_addr.s_addr = inet_addr("127.0.0.1"); //
	address.sin_port = htons(9737);
	len = sizeof(address);
	/* Now connect our socket to the server's socket. */
	result = connect(sockfd, (struct sockaddr *)&address, len);
	if(result == -1) {
		perror("oops: client2");
		exit(1);
	}else{
		printf("connect success...\n");
	}
	/* We can now read/write via sockfd. */
	int res ;
		printf("try to open file...\n");
		int myfd = open("data.dat", O_RDONLY | O_EXCL);
                if(myfd == -1) perror("");
		printf("open file success\n");
		printf("start to read file to server...\n");
                copy_file(myfd, sockfd);
        


	close(sockfd);
	close(myfd);
	printf("Client Exit now\n");
	exit(0);
}




unsigned long copy_file(int from_fd,int to_fd)
{
   int bytesread, byteswritten;
   int totalbytes=0;
   char buf[512];
   char *bp;   
   int BLKSIZE = 8;
   
   while (bytesread = read(from_fd, buf, BLKSIZE)) {
      if ((bytesread == -1) && (errno != EINTR))
         break;          /* real error occurred on the descriptor */
 	printf("byteread=%d\n", bytesread);
           bp = buf;
         while(byteswritten = write(to_fd, bp, bytesread)) {
             if ((byteswritten == -1) && (errno != EINTR)){
                printf("write error\n");
                break;
             }else{
             	printf("wriete success %d\n", byteswritten);
             }
               
            if (byteswritten > 0) {
                bp += byteswritten;
                bytesread -= byteswritten;
                totalbytes+=byteswritten;
             }
         }
	printf("break1\n");
      
   }    
	printf("break2\n"); 
   return totalbytes;
}   

