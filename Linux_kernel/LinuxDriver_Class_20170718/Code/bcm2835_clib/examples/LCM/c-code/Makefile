CC=gcc
INC=-I./
CFLAG=-D_PI2_

PROGRAMS=lcm
VPATH=../../src

all: lcm

lcm: bcm2835.o lib_lcd1602.c
	$(CC) -c lib_lcd1602.c -o lib_lcd1602.o $(INC) $(CFLAG)
	$(CC) test.c lib_lcd1602.o bcm2835.o  -o $@ $(INC) $(CFLAG)


bcm2835.o: bcm2835.c
	$(CC) -c $^  $(INC) $(CFLAG)

clean:
	rm *.o; rm $(PROGRAMS)
