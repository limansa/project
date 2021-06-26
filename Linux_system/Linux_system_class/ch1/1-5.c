#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>

typedef struct {
    int integer;
    char string[12];
} RECORD;

#define NRECORDS (50)
int main()
{
    RECORD record;
    int i, f;
    FILE *fp;
    fp = fopen("records.dat","w+");
    for(i=0; i<NRECORDS; i++) {
        record.integer = i;
        sprintf(record.string,"RECORD-%d",i);
        fprintf(stdout,"RECORD-%d\n",i);
        fwrite(&record,sizeof(record),1,fp);
    }
    fclose(fp);

/*  We now change the integer value of record 43 to 143
    and write this to the 43rd record's string.  */

    fp = fopen("records.dat","r+");
    fseek(fp,43*sizeof(record),SEEK_SET);
    fread(&record,sizeof(record),1,fp);

    record.integer = 999;
    sprintf(record.string,"RECORD-%d",record.integer);

    fseek(fp,43*sizeof(record),SEEK_SET);
    fwrite(&record,sizeof(record),1,fp);
    fclose(fp);
return 0;
}
