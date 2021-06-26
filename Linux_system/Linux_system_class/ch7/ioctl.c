#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <net/if.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>


/*
SIOCGIFADDR
SIOCGIFDSTADDR
SIOCGIFBRDADDR
SIOCGIFNETMASK
SIOCGIFFLAGS
SIOCGIFMTU
open("/proc/net/dev", O_RDONLY) 

*/

void get_ip(char * ifname);
void get_mac(char * ifname);
#define FMT "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d"
struct net_info {

char face[16];
/*rx*/
int rxbytes;
int rxpackets;
int rxerrs;
int rxdrop;
int rxfifo;
int rxframe;
int rxcompressed;
int rxmulticast;
/*tx*/
int txbytes;
int txpackets;
int txerrs;
int txdrop;
int txfifo;
int txcolls;
int txcarrier;
int txcompressed;
};

void read_net_statistic( struct net_info *info);
int main()
{
  char *name="eth0";
  struct net_info net;
  get_ip(name);
  get_mac(name);
   read_net_statistic(&net);
  printf("%s RX:%d bytes,TX:%d bytes\n",net.face,net.rxbytes,net.txbytes);
 
  return 0;

}

//Example 1: IP address
void get_ip(char * ifname)
{

        int  fd;
        struct ifreq ifr;
	char buf[32];
        fd = socket(AF_INET, SOCK_DGRAM, 0);
         strcpy(ifr.ifr_name,ifname);
        if (ioctl( fd, SIOCGIFADDR, &ifr) < 0)
                perror("ioctl");
        close(fd);
        snprintf(buf,32,"%s", inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr));
        printf("%s\n",buf);


 }

//Example 2: Mac address

void get_mac(char * ifname)
{

 int  fd;
 struct ifreq ifr;
 fd = socket(AF_INET, SOCK_DGRAM, 0);
 ifr.ifr_addr.sa_family = AF_INET;
 strcpy(ifr.ifr_name, ifname);
 ioctl(fd, SIOCGIFHWADDR, &ifr);
 close(fd);

  printf("%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",
         (unsigned char)ifr.ifr_hwaddr.sa_data[0],
         (unsigned char)ifr.ifr_hwaddr.sa_data[1],
         (unsigned char)ifr.ifr_hwaddr.sa_data[2],
         (unsigned char)ifr.ifr_hwaddr.sa_data[3],
         (unsigned char)ifr.ifr_hwaddr.sa_data[4],
         (unsigned char)ifr.ifr_hwaddr.sa_data[5]);

}











void read_net_statistic( struct net_info *info)
{


 FILE *read_fp;
 char buffer[BUFSIZ + 1];
 int chars_read;
 char *s;

 long tx_bytes=0,rx_bytes=0;
 memset(buffer, '\0', sizeof(buffer));
 read_fp = popen("cat /proc/net/dev", "r");
 int n;

 if (read_fp == NULL) 
	 return ;
 
   chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
   if (chars_read > 0) {
	  // printf("Output was:-\n%s\n", buffer);
	   s=strstr(buffer,"eth0");
	   if (!s) {
		  fprintf(stderr,"cannot get eth0 interface");
	      return ;
	   }
	 
	  sscanf(s,FMT,info->face,&info->rxbytes,&info->rxpackets,&info->rxerrs, 
     &info->rxdrop,&info->rxfifo,&info->rxframe,&info->rxcompressed,&info->rxmulticast,
 &info->txbytes,&info->txpackets,&info->txerrs,&info->txdrop,&info->txfifo,
  &info->txcolls,&info->txcarrier,&info->txcompressed);
   }


	 pclose(read_fp);
 }

	 












