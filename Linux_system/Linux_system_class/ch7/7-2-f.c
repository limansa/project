/* Server*/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
void
childWait (int sig) 
{  
	printf ("OUCH! - I got signal %d\n", sig);
	int stat_val;
	pid_t child_pid;
	child_pid = wait (&stat_val);
	printf ("Child has finished: PID = %d\n", child_pid);
	if (WIFEXITED (stat_val))
	{
	      printf ("Child exited with code %d\n", WEXITSTATUS (stat_val));
	}
	return;
}
unsigned long copy_file(int from_fd,int to_fd);
void handleRequest(int client_sockfd);
int main()
{ 
	int server_sockfd;
	int server_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	/* Create an unnamed socket for the server. */
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	/* Name the socket. */
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(9737);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
	/* Create a connection queue and wait for clients. */
	listen(server_sockfd, 5);
        int clientCnt = 0;

//handle signal

	struct sigaction act;
  	act.sa_handler = childWait;
  	act.sa_flags = 0; //if mark, we will get memory session error
  	sigaction (SIGCHLD, &act, 0);

	while(1) {
		int client_sockfd;
		int client_len;
		int ret
		/* Accept a connection. */
		printf("server waiting\n");
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,
		(struct sockaddr *)&client_address, &client_len);
		
		printf("\n[Cient Connect]IP=%s Port=%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
		 ret= fork();
		if(ret == -1){
			perror("fork error\n");
		} else if(ret == 0){
			printf("Iam child...pid=%d\n", getpid());
			close(server_sockfd);
			handleRequest(client_sockfd);
			break;
			
		}else{
			printf("Iam parent...pid=%d\n", getpid());
			close(client_sockfd);
			sleep(2);
		}
	}
        return 0;
}

void handleRequest(int client_sockfd){
		/* We can now read/write to client on client_sockfd. */
		sleep(5);
		printf("Iam child, and task ok, exit now...pid=%d\n", getpid());
		exit(0);
}


unsigned long copy_file(int from_fd,int to_fd)
{
   int bytesread, byteswritten;
   int totalbytes=0;
   char buf[512];
   char *bp;   
   int BLKSIZE = 512;
   
   while (bytesread = read(from_fd, buf, BLKSIZE)) {
      if ((bytesread == -1) && (errno != EINTR))
         break;          /* real error occurred on the descriptor */
 
           bp = buf;
         while(byteswritten = write(to_fd, bp, bytesread)) {
             if ((byteswritten == -1) && (errno != EINTR))
                break;
               
            if (byteswritten > 0) {
                bp += byteswritten;
                bytesread -= byteswritten;
                totalbytes+=byteswritten;
             }
         }
      
   }     
   return totalbytes;
}   
