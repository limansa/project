/* Server*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

void child_term(int sig) {
	pid_t pid;
	printf("Recieve signal %d\nTerminated child PID=%d\n",sig,wait(NULL));
}

int main()
{ 
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	
	sigset_t socket_sigset;
	struct sigaction socket_sigact;
	
	
	sigemptyset(&socket_sigset);
	sigaddset(&socket_sigset,SIGCHLD);
	socket_sigact.sa_handler=child_term;
	sigaction(SIGCHLD,&socket_sigact,NULL);


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
		client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);
		
		child_pid=fork();
		if (child_pid) {
			

			close(client_sockfd);
			printf("Child pid=%d\n",child_pid);


		}
		else	{
			close(server_sockfd);
			printf("Client address is %s,port is %d %d(with ntohs)\n",inet_ntoa(client_address.sin_addr),client_address.sin_port,ntohs(client_address.sin_port));
			res = read(client_sockfd, buf, 128);
			printf("char from client %s\n", buf);
			write(client_sockfd, &ch, strlen(ch)+1);

			sleep(5);		
			close(client_sockfd);

			exit(0);
		}

		
		/* We can now read/write to client on client_sockfd. */
		

		
		//printf("res = %d\n",res);

		

	}
	close(server_sockfd);
	return 0;
}
