
CC=gcc
INC=-I./ -I../include
CFLAG=

all: lib_i2c.o bcm2835.o si7020.o lib_i2c_gpio.o

si7020.o: si7020.c
	$(CC) -c si7020.c $(INC)

lib_i2c.o: lib_i2c.c
	$(CC) -c lib_i2c.c $(INC)

lib_i2c_gpio.o: lib_i2c_gpio.c
	$(CC) -c lib_i2c_gpio.c $(INC)

bcm2835.o: lib_i2c.c
	$(CC) -c bcm2835.c $(INC)

clean:
	rm *.o
