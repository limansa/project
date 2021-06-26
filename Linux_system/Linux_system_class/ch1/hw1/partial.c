/////////////////////////////////////////////////////////////////////////////
/* Input file type */

typedef enum { KERNEL=1,CONFIG, ROOTFS ,BOOT_COCE} TYPE_T;

typedef struct _sector {
	TYPE_T type;
	char filename[80];
	unsigned long offset;
	unsigned long size;
} SECTOR_T;


static SECTOR_T sector[]={
    {KERNEL, "bzImage",    		0x0		,0x170000},
    {CONFIG, "config.bin",		0x170000,0x10000},
    {ROOTFS, "ext2.bin",		0x180000,0x260000},
    {BOOT_COCE, "redboot.bin", 0x3e0000,0x20000},
    {0, 0, 0,0},

};