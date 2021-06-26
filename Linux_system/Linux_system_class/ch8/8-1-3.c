#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
	FILE *read_fp;
	char buffer[BUFSIZ + 1];
	int chars_read;
	char cmdbuf[128];
	memset(buffer, '\0', sizeof(buffer));
	if (argc!=2) {
		printf("usage: %s <ip>\n",argv[0]);
       return -1;
    } 
	sprintf(cmdbuf,"ping %s -c 1",argv[1]);
	read_fp = popen(cmdbuf, "r");

	if (read_fp != NULL) {
		chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
			buffer[chars_read-1] = '\0';
		//	printf("%s\n",buffer);
			if (strstr(buffer,"1 received"))
				printf("host %s is alive!\n",argv[1]);
			else printf("host %s is NOT alive\n",argv[1]);
		}
	
		pclose(read_fp);
		exit(EXIT_SUCCESS);
	
	exit(EXIT_FAILURE);
}
