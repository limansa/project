
 /*i2cdetect.c - a user-space program to scan for I2C devices 
 Copyright (C) 1999-2004  Frodo Looijaard <frodol@dds.nl>, and ark D. Studebaker <mdsxyz123@yahoo.com>
    Copyright (C) 2004-2010  Jean Delvare <khali@linux-fr.org>*/
/*  We start by defining a RECORD structure
    and then create NRECORDS versions each recording their number.
    These are appended to the file records.dat.  */

#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
typedef struct {
    int integer;
    char string[12];
} RECORD;

#define NRECORDS (50)

int main()
{
    RECORD record, *mapped;
    int i, f;
    FILE *fp;

    fp = fopen("records.dat","w+");
    for(i=0; i<NRECORDS; i++) {
        record.integer = i;
        sprintf(record.string,"RECORD-%d",i);
        fwrite(&record,sizeof(record),1,fp);
    }
    fclose(fp);

    f = open("records.dat",O_RDWR);
    mapped = (RECORD *)mmap(0, NRECORDS*sizeof(record), 
                          PROT_READ|PROT_WRITE, MAP_SHARED, f, 0);

    mapped[43].integer = 999;
    sprintf(mapped[43].string,"RECORD-%d",mapped[43].integer);

    msync((void *)mapped, NRECORDS*sizeof(record), MS_ASYNC);
    munmap((void *)mapped, NRECORDS*sizeof(record));
    close(f);

    exit(0);
}

