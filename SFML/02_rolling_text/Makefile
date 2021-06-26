CC:=gcc
CPP:=g++
#CFLAGS = 
#INC = -I<sfml-install-path>/include
#LIB = -L<sfml-install-path>/lib
LIB = -lsfml-graphics -lsfml-window -lsfml-system

all: sfml-app

sfml-app:main.o
	g++ -Wall main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -ansi

main.o:main.cpp
	g++ -Wall -c main.cpp -ansi

clean:
	rm -f sfml-app main.o