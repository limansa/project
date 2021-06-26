
SUBDIRS = src/frammis src/cooker
CC=arm-linux-gcc
##CC=gcc
export CC     
subdirs:
	@for dir in $(SUBDIRS); do \
           $(MAKE) -C $$dir  || exit 1 ; \
        done
clean:
	@for dir in $(SUBDIRS); do \
	$(MAKE) -C $$dir clean  || exit 1 ; \
	done

