CC=gcc
INC=-I./include

all: main.o
	cd ./src;make
	mv ./src/*.o ./
	$(CC) *.o -o app

main.o: main.c
	$(CC) -c main.c $(INC)

clean:
	rm *.o;rm app
