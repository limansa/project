CCPREFIX=arm-linux-gnueabihf-
KERNEL_SOURCE_PATH=/lib/modules/$(shell uname -r)/build
obj-m += bcm_mini_uart.o

all:
	make  ARCH=arm CROSS_COMPILE=${CCPREFIX} -C ${KERNEL_SOURCE_PATH} M=$(PWD) modules

clean:
	make  ARCH=arm CROSS_COMPILE=${CCPREFIX} -C ${KERNEL_SOURCE_PATH} M=$(PWD) clean
