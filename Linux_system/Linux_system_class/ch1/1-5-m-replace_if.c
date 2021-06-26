#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h> // for S_IRUSR and S_IWUSR
#include <string.h> // for memset()

typedef struct {
    int integer;
    char string[12];
} RECORD;

#define NRECORDS (50)
int main()
{
    RECORD record;
    int i;
    //int f; // Useless
    //FILE *fp;
    int fd;
    //fp = fopen("records.dat","w+");
    fd = open("records-fd.dat", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    for(i=0; i<NRECORDS; i++) {
        memset(&record, 0, sizeof(record));
	record.integer = i;
        sprintf(record.string,"RECORD-%d",i);
        fprintf(stdout,"RECORD-%d\n",i);
        //fwrite(&record,sizeof(record),1,fp);
        write(fd, &record, sizeof(record));
    }
    //fclose(fp);
    close(fd);

/*  We now change the integer value of record 43 to 143
    and write this to the 43rd record's string.  */

    //fp = fopen("records.dat","r+");
o    fd = open("records-fd.dat", O_RDWR);
    //fseek(fp,43*sizeof(record),SEEK_SET);
    lseek(fd, 43*sizeof(record), SEEK_SET);
    //fread(&record,sizeof(record),1,fp);
    read(fd, &record, sizeof(record));

    record.integer = 999;
    sprintf(record.string,"RECORD-%d",record.integer);

    //fseek(fp,43*sizeof(record),SEEK_SET);
    lseek(fd, 43*sizeof(record), SEEK_SET);
    //fwrite(&record,sizeof(record),1,fp);
    write(fd, &record, sizeof(record));
    //fclose(fp);
    close(fd);

    return 0;
}
