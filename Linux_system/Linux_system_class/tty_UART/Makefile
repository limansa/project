CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar

ALL :  ext_uart 

gps:  ext_uart.c 

	$(CC) -o ext_uart   ext_uart.c 
 	
clean :
	rm -rf ext_uart
