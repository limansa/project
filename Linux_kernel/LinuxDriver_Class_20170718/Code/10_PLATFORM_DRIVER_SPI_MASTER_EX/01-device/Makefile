
obj-m	+= platform_device_spi.o

all drivers:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C  /lib/modules/$(shell uname -r)/build M=$(PWD) clean
