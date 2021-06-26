#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    char c;
    int in, cnt,n;
    off_t cur;

    in = open("file.in", O_RDONLY);
    if ( in < 0 ) goto error;

    cnt = 1;
    cur = lseek(in,-1, SEEK_END);
    n=-1;
    while (read(in, &c, 1) == 1) {
        write(1, &c, 1);
	n -=1;
        cur = lseek(in, (n), SEEK_END);
        if (cur < 0) {
            break;
        }
    }

    close(in);

        return 0;
error:
    fprintf(stderr,"file open error\n");
    exit(0);
}
