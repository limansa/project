#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main(void){
	int fd[2];
	int rc;
	int execl1 = -99,   execl2 = -99;
	rc = pipe(fd);
	if(0 == fork()){
        close(fd[0]);
		if (dup2(fd[1], 1)==-1) 
		    perror("dup2:");   
		// stdout
		execl1 = execl("/bin/cat", "cat", "/etc/passwd", (char *)0); 
		

	} 

	
	if(0 == fork()){
		close(fd[1]);
		if(dup2(fd[0], 0)==-1) perror("dup2:");  //stdin
		execl2 = execl("/usr/bin/wc", "wc", "-l", (char *)0);
		
	} 
    close(fd[0]);	
    close(fd[1]);
	wait();
    wait();

return 0;
}
