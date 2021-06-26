int com_init(int fd,char* device,int baudrate,struct termios oldtio,struct termios newtio);
void com_close(int fd,struct termios oldtio);
void com_write(int fd,char *bytes, int size);

int com_init(int fd,char* device,int baudrate,struct termios oldtio,struct termios newtio)
{
        fd=open(device, O_RDWR|O_NDELAY );
        if (fd < 0)
        {
                perror("COM PORT OPEN");
                return -1;
        }

        tcgetattr(fd , &oldtio);
        memset(&newtio,'0',sizeof(newtio));
        newtio.c_cflag = baudrate|CS8|CLOCAL|CREAD ;
        newtio.c_iflag = IGNPAR ;
        newtio.c_lflag &= ~ICANON;
        newtio.c_lflag &= ~ECHO;
        newtio.c_lflag &= ~ISIG;
        newtio.c_oflag = 0;
        newtio.c_cc[VMIN] = 2;
        newtio.c_cc[VTIME] = 0;
        tcflush(fd , TCIFLUSH) ;
        tcsetattr(fd , TCSANOW , &newtio );
        return fd;
}
void com_close(int fd,struct termios oldtio){
        close(fd);
        tcsetattr(fd, TCSANOW, &oldtio);
}
void com_write(int fd,char *bytes, int size)
{
        int len, ret;
        len = 0;
        while (len < size) {
        if ((ret = write(fd, bytes, size - len)) == -1)
                switch (errno) {
                case EAGAIN:
                  fprintf(stderr, "* EAGAIN *\n");
                  ret = 0;
                  break;
                case EINTR:
                  fprintf(stderr, "* EINTR *\n");
                  ret = 0;
                  break;
                default:
                        perror("gpio_serial_write");
                        exit(1);
                }

                len += ret;
        }
}
