obj-m += app
CC=gcc
INC=-I./ -I./include
CFLAG=-lpthread
DEBUG=-DMYDEBUG

make:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
app:
	$(CC) ./src/*.c ./*.c -o app $(INC) $(CFLAG)
