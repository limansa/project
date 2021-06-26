#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd;
    struct stat     filestat;
    off_t           alignmentsize;

    if (argc != 2)
    {
        printf("padding <filename>\n");
        return 0;
    }

    // open file
    fd = open(argv[1], O_RDWR | O_EXCL);
    if (fd < 0)
    {
        printf("%s\n", strerror(errno));
        return 0;
    }

    // get filesize
    fstat(fd, &filestat);

    if (filestat.st_size >= (1ul << 31))
    {
        close(fd);
        perror("File great than 2GB, it can not padding.");
        return 0;
    }

    // check alignment size
    alignmentsize = 1;

    while (filestat.st_size > alignmentsize)
    {
        alignmentsize <<= 1;
    }

    printf("File %s is %ld bytes, need padding %ld bytes.\n", argv[1], filestat.st_size, (alignmentsize - filestat.st_size));

    if (ftruncate(fd, alignmentsize) == -1)
    {
        printf("%s\n", strerror(errno));
    }

    close(fd);

    return 0;
}