CC:=gcc
CPP:=g++
#CFLAGS = 
#INC = -I<sfml-install-path>/include
#LIB = -L<sfml-install-path>/lib
LIB = -lsfml-graphics -lsfml-window -lsfml-system

all: sfml-app

sfml-app:main.o
	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

main.o:main.cpp
	g++ -c main.cpp

clean:
	rm -f sfml-app main.o