#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
FILE *write_fp;
int i=0;
char buffer[BUFSIZ + 1];
sprintf(buffer, "Hello Ittraining...\n");
fprintf(stdout,"%s",buffer);
write_fp = popen("wc -c ", "w");
if (write_fp != NULL) {
   while (i<3) {
	fwrite(buffer, sizeof(char), strlen(buffer), write_fp);
	i++;
	printf("input text:\n");
	scanf("%s",buffer);
   }

pclose(write_fp);
exit(EXIT_SUCCESS);
}
exit(EXIT_FAILURE);
}
