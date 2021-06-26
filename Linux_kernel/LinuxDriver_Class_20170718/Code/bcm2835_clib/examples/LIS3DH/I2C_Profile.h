
#ifndef __I2C_Pro_H
#define __I2C_Pro_H

#include "gpio_ini.h"
#include<bcm2835.h>
#include<stdint.h>



typedef struct {
	short 	x;
	short	y;
	short	z;
} LIS3DHSample;


// ==
#define SDA_Low bcm2835_gpio_write(SDA, LOW)
#define SCL_Low bcm2835_gpio_write(SCL, LOW)
#define SCL_High bcm2835_gpio_write(SCL, HIGH)
#define SDA_High bcm2835_gpio_write(SDA, HIGH)


// ==
#define LIS3DH_ADR 0x32 
#define LIS3DH_MULTI_OUT_Y_L 0xA8    //28

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define CTRL_REG6 0x25
void delay_I2C(unsigned char time);
unsigned char i2c_read(void);
void i2c_write(unsigned char dat);
void i2c_ack(void); 
void i2c_stop(void);
void i2c_start(void);
extern void i2c_write_data(unsigned char LIS3DH_Slave_Address, unsigned char LIS3DH_Register, unsigned char LIS3DH_Data);
extern unsigned int Read_Sensor_Data(void);

#endif
