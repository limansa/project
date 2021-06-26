CC:=gcc
CPP:=g++

#CFLAGS = -Wall -Waddress -Wbool-compare -Wbool-operation -Wc++11-compat -Wc++14-compat -Wunused-value -Wchar-subscripts 
#CFLAGS += -Wcomment -Wformat -Wint-in-bool-context -Winit-self -Wlogical-not-parentheses -Wmaybe-uninitialized 
#CFLAGS += -Wmemset-elt-size -Wmemset-transposed-args -Wmisleading-indentation -Wno-attributes -Wmissing-braces
#CFLAGS += -Wunused-macros -Wnarrowing -Wnonnull -Wnonnull-compare -Wopenmp-simd -Wparentheses -Wpointer-sign 
#CFLAGS += -Wreorder -Wrestrict -Wreturn-type -Wsequence-point -Wsign-compare -Wno-pointer-sign -Wsizeof-pointer-memaccess 
#CFLAGS += -Wstrict-aliasing -Wstrict-overflow=1 -Wswitch -Wtautological-compare -Wtrigraphs -Wuninitialized -Wunknown-pragmas 
#CFLAGS += -Wunused-function -Wunused-label -Wunused-value -Wunused-variable -Wvolatile-register-var
CFLAGS =  -Wall -Wextra -Werror --std=c++11
#INC = -I<sfml-install-path>/include
#LIB = -L<sfml-install-path>/lib
LIB = -lsfml-graphics -lsfml-window -lsfml-system

all: sfml-app

sfml-app:main.o
	g++ $(CFLAGS) main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -ansi

main.o:main.cpp
	g++ $(CFLAGS) -Wextra -Wpedantic -Wall -c main.cpp -ansi

clean:
	rm -f sfml-app main.o