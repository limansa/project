/* Server*/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


#include <sys/wait.h>
#include <unistd.h>
void reap_child (int sig);
int main()
{ 
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	
	signal(SIGCHLD,reap_child);

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
		pid_t child_pid;

		printf("server waiting\n");
		/* Accept a connection. */
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,
		(struct sockaddr *)&client_address, &client_len);
		
		/* We can now read/write to client on client_sockfd. */
		if ((child_pid=fork())==0) {
			res = read(client_sockfd, buf, 128);
			sleep(5);
			//printf("res = %d\n",res);
			printf("char from client %s\n", buf);
			write(client_sockfd, &ch, sizeof(ch));
			close(client_sockfd);
	 		exit (0);
		} else if (child_pid>0) {
			 close(client_sockfd);

		} else {
		   printf("fork() failed\n");
	
		}


	}
}


void reap_child (int sig)
{
    pid_t child;
    child=wait(NULL);
    printf("child %d exit!!\n",child);



}



