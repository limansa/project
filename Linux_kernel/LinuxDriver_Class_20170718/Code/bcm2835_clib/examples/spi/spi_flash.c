// spi.c
//
// Example program for bcm2835 library
// Shows how to interface with SPI to transfer a byte to and from an SPI device
//
// After installing bcm2835, you can build this 
// with something like:
// gcc -o spi spi.c -l bcm2835
// sudo ./spi
//
// Or you can test it before installing with:
// gcc -o spi -I ../../src ../../src/bcm2835.c spi.c
// sudo ./spi
//
// Author: Mike McCauley
// Copyright (C) 2012 Mike McCauley
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $

#include <bcm2835.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO
// Use for testing
//        bcm2835_set_debug(1);
    uint8_t data[10]={0};
      if (!bcm2835_init())
	return 1;

    bcm2835_spi_begin();
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE1);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

    char tbuf[] = { 0x9f, 0x00, 0x00,0x00}; // Read DeviceID of   MX25L4005A
    char rbuf[10]; 
    bcm2835_spi_transfernb(tbuf,rbuf,sizeof(tbuf));
 //    bcm2835_spi_transfern(tbuf,sizeof(tbuf));
    // buf will now be filled with the data that was read from the slave
//    printf("Device ID: %02X \n", buf[2]);
    printf("Read ID from MX25L4005A for RDID Command: %02X %02X %02X \n", rbuf[1],rbuf[2],rbuf[3]);
//    printf("Read from MX25L4005A for RDID Command: %02X %02X %02X \n", tbuf[1],tbuf[2],tbuf[3]);

    bcm2835_spi_end();
    bcm2835_close();
    return 0;
}

