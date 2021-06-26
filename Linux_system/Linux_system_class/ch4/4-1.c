#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
printf("Running ls with system\n");
//system("ls -al");
execl("/bin/ls","ls","-al",(char *)0);

printf("====Done.======\n");
exit(0);
}
