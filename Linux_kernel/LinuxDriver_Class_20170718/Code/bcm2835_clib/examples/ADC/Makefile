CC=gcc
INC=-I./ -I../../src
CFLAG=-D_PI2_

PROGRAMS=adc
VPATH=../../src

all: $(PROGRAMS)

adc: bcm2835.o mcp3008.c
	$(CC) main.c mcp3008.c  bcm2835.o  -o $@ $(INC) $(CFLAG)


bcm2835.o: bcm2835.c
	$(CC) -c  $^  $(INC) $(CFLAG)

clean:
	rm *.o; rm $(PROGRAMS)
