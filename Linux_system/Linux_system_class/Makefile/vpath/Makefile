

#Make all the top-level targets the makefile knows about 

VPATH= src include
all: frammis cooker
CPPFLAGS=-Iinclude


frammis: frammis.c frammis.h
	gcc $< -o $@ $(CPPFLAGS)
	
cooker: cooker.c include/cooker.h	
	gcc $< -o $@
#.PHONY: all clean

clean:
	rm -rf frammis
	rm -rf cooker
