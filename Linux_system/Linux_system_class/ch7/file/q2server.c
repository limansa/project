/* Server*/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

#define FILEFMT 2



int main()
{ 
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	/* Create an unnamed socket for the server. */
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	/* Name the socket. */
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(9741);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
	/* Create a connection queue and wait for clients. */
	listen(server_sockfd, 5);
	while(1) {
		char ch[] = "ByeBye";
		char buf[128];
		char c;
		int fd;
		int size;

		char file_name[64];
		printf("server waiting\n");
		/* Accept a connection. */
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,
		(struct sockaddr *)&client_address, &client_len);
		/* We can now read/write to client on client_sockfd. */
	
		size = 0;


		#if (FILEFMT==1)
	      char template[] = "fileXXXXXX";
          char *ptr;
                ptr = (char *)mkstemp(template);
		if (!ptr) {
		    printf("mktemp() error!\n");
		    break;
		}
		 	
		#elif (FILEFMT==2)
		time_t rawtime; 
		struct tm * timeinfo; 
		time ( &rawtime ); 
		timeinfo = localtime ( &rawtime );
	
		sprintf(file_name,"%02d%02d%02d.jpg",

		timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
		
	
	    #endif



		fd = open(file_name,O_WRONLY|O_CREAT,0666);
		printf("file name: %s\n",file_name);

		
		    
		

	
		 if (fd < 0) {
		        perror("client:");

        	}



		size=copy_file(client_sockfd,fd);
		
		//printf("res = %d\n",res);
		printf("size from client %d\n", size);
		close(fd);
		close(client_sockfd);
	}
}
