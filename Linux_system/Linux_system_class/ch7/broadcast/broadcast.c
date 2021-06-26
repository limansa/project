#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>



#define BROADCAST_PORT 12345
#define BROADCAST_GROUP "192.168.5.255"

int main(int argc, char *argv[])
{
    struct sockaddr_in addr;
   
    int fd;
     int broadcastEnable=1;
     int ret;
    char *message = "Hello Ittraining!";
   

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        exit(1);
    }


    /* set up destination address */
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(BROADCAST_GROUP);
    addr.sin_port=htons(BROADCAST_PORT);

    
     ret=setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
     if (ret<0)
     	  perror("setsockopt:");


    while (1)
    {
        if (sendto(fd, message, strlen(message)+1, 0,(struct sockaddr *) &addr, sizeof(addr)) < 0)
        {
            perror("sendto");
            exit(1);
        }
        sleep(3);
   
    }
}
