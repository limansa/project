
#CROSS=arm-linux-
CFLAG=-lmenu -lncurses

.PHONY : all rs232_send rs232_recv

all: rs232_send rs232_recv

rs232_send:
	gcc -o rs232_send rs232_send.c $(CFLAG)
rs232_recv:
	$(CROSS)gcc -o rs232_recv rs232_recv.c

clean:
	@rm -vf rs232_send rs232_recv *.o *~
