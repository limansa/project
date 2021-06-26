#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <assert.h>
int main()
{
int fd;
int rc;
struct stat statbuf;
 char sample1[]="hello";
 char sample2[]="world";
/* Create the file */
printf("Creating file\n");
fd=open("junk.out",O_WRONLY|O_CREAT|O_TRUNC,0666);
assert(fd>=0);
rc=write(fd,sample1,strlen(sample1));
assert(rc==strlen(sample1));
close(fd);
/* Append to the file */
printf("Appending to file\n");
fd=open("junk.out",O_WRONLY|O_APPEND);
assert(fd>=0);
printf(" locking file\n");
//rc=flock(fd, LOCK_EX);
//assert(rc==0);
/* sleep so you can try running two copies at one time */
printf(" sleeping for 10 seconds\n");
sleep(10);
printf(" writing data\n");
rc=write(fd,sample2,strlen(sample2));
assert(rc==strlen(sample2));
printf(" unlocking file\n");
//rc=flock(fd, LOCK_UN);
//assert(rc==0);
close(fd);



 return 0;
}
