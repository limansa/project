/*
 *      utility to merge all binary into one image
 *
 *      www.ittraining.com.tw
 *
 *
 *
 */
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#ifdef WIN32
	#include <io.h>
#endif

#define FLASH_SIZE 0x400000
#define FLASH_BIN  "flash.bin"
#define FLASH_ERASE_SIZE  0x10000

/////////////////////////////////////////////////////////////////////////////
/* Input file type */

typedef enum { KERNEL=1,CONFIG, ROOTFS ,BOOT_COCE} TYPE_T;

typedef struct _sector {
	TYPE_T type;
	char filename[80];
	unsigned long offset;
	unsigned long size;
} SECTOR_T;

/////////////////////////////////////////////////////////////////////////////
static char *copyright="Copyright (c) ittraining Corp., 2011. All Rights Reserved.";
static char *version="1.0";

/*should reference kernel MTD maps*/
static SECTOR_T sector[]={
    {KERNEL, "bzImage",    		0x0		,0x170000},
    {CONFIG, "config.bin",		0x170000,0x10000},
    {ROOTFS, "ext2.bin",		0x180000,0x260000},
    {BOOT_COCE, "redboot.bin", 0x3e0000,0x20000},
    {0, 0, 0,0},

};


void dump_mem(void *ptr, int size)
{   
    int i;
			    
    printf("\n");
    for(i=0; i < size; i++)
    {   
        printf("%4.2x", (unsigned )(((unsigned char*)ptr)[i]));
        if((i%16 == 0) && (i!=0))
            printf("\n");
    }
    printf("\n");
}


////////////////////////////////////////////////////////////////////////////////
static void showHelp(void)
{
	printf("\n Utility to merge binary.\n");
	printf("%s Ver %s.\n\n", copyright, version);


}

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    int i=0;
    int fh;
    int outfh;
    char buf[FLASH_SIZE];
    char cmd[128];
    struct stat status;
	//generate a 4M empty file
    sprintf(cmd,"dd if=/dev/zero of=%s bs=%d count=%d",FLASH_BIN,FLASH_ERASE_SIZE,FLASH_SIZE/FLASH_ERASE_SIZE);
    system(cmd);

    outfh = open(FLASH_BIN, O_RDWR);
	if ( outfh == -1 ) {
		printf("Open output file flash.bin error!\n");
		exit(1);
	}
	//check all sectors
  //  check_sector(&sector[0]);

	//OK , write to file
    for (i=0;sector[i].type!=0;i++) {
	  fh = open(sector[i].filename, O_RDONLY);

	  if ( fh == -1 ) {
		printf("Open %s file error!\n",sector[i].filename);
		exit(1);
	 }
	// check input file and allocate buffer
	 if ( fstat(fh, &status) < 0 ) {
		printf("Error : Can't get file size [%s]\n", sector[i].filename);
		exit(1);
	 }
	  if (status.st_size > sector[i].size) {
		 printf("Error : [%s] file size %#x is larger than %#x\n", sector[i].filename,status.st_size,sector[i].size);
    	 exit(1);
	 	}

	  lseek(outfh,sector[i].offset, SEEK_SET);

	  if ( read(fh, buf, status.st_size) != status.st_size) {
		printf("Read %s file error!\n",sector[i].filename);
		close(fh);
		exit(1);
	  }

	  if ( write(outfh, buf, status.st_size) != status.st_size) {
	 		printf("Write %s file error!\n",sector[i].filename);
	 		close(outfh);
	 		exit(1);
	 	 }

	   close(fh);

    }

    close(outfh);

    printf("Generate Manufacture Firmware Image (%dM) Successfully \n",FLASH_SIZE/1024/1024);

    return 0;
}

