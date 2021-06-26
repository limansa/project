
SUBDIRS = src/frammis src/cooker
CC=arm-linux-gcc
export CC     


#include cross.make

.PHONY: subdirs $(SUBDIRS)
	     
subdirs: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

