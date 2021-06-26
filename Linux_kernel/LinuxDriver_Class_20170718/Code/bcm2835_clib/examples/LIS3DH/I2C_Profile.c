#include "I2C_Profile.h"
#include <bcm2835.h>
#include "Gsensor.h"
#include "gpio_ini.h"
#include <stdio.h>
extern unsigned char gsensor_value[6];

LIS3DHSample sample;

//******************** I2C SUB *******************+++
void i2c_start(void)
{
	SDA_Low;
	delay_I2C(1);//start
	SCL_Low;
	delay_I2C(2); //
}

//................
void i2c_stop(void)
{
	SCL_High;
	delay_I2C(1); //
	SDA_High;              //stop	
	delay_I2C(1);
}

//................
void i2c_ack(void)
{
	SDA_High;
	delay_I2C(1);                
	SCL_High;
	delay_I2C(3);
	SCL_Low;
	delay_I2C(1);
	SDA_Low;
	delay_I2C(1);             
}
//................
void i2c_mack(void)
{
	SDA_Low;
	delay_I2C(2);                 
	SCL_High;
	delay_I2C(1);	  
	SCL_Low;
	delay_I2C(1);
	SDA_High;
	delay_I2C(1);             
}
//................
void i2c_write(unsigned char dat)
{
 	unsigned char i;
 	bcm2835_gpio_fsel(SDA, BCM2835_GPIO_FSEL_OUTP);
 	for(i=0;i<=7;i++)
    {
      if(dat&0x80)
       	SDA_High;
      else 
       	SDA_Low;
       
       delay_I2C(1);
       SCL_High;
       delay_I2C(1);
       SCL_Low;
       delay_I2C(1);
       SDA_Low;
       delay_I2C(1);
       dat<<=1;
    }
    
    i2c_ack();
}
//..............
unsigned char i2c_read(void)
{
	unsigned char i,dat=0;
    int SDA_Pin;
	bcm2835_gpio_fsel(SDA, BCM2835_GPIO_FSEL_INPT); 
	for(i=0;i<=7;i++)
	{
		SCL_High;
		dat <<= 1;
		delay_I2C(1);
        SDA_Pin= bcm2835_gpio_lev(SDA);
		if(SDA_Pin==1)
		 dat|=0x01;
		else
 	     dat&=0xfe;		 	
		delay_I2C(1);
		SCL_Low;
		delay_I2C(2); 
	}	
	bcm2835_gpio_fsel(SDA, BCM2835_GPIO_FSEL_OUTP);
	SDA_Low;  
	return dat;
}

void delay_I2C(unsigned char time)
{
	unsigned char x,y;

 	for(x=0;x<=time;x++)
      {
          for(y=0;y<=100;y++);
      }
}
//******************** I2C SUB ******************* --
void i2c_write_data(unsigned char LIS3DH_Slave_Address, unsigned char LIS3DH_Register, unsigned char LIS3DH_Data)
{
	i2c_start();
	i2c_write(LIS3DH_Slave_Address);
	i2c_write(LIS3DH_Register);
	i2c_write(LIS3DH_Data);
	i2c_stop();
}

//Only Read sensor data (Only X axis "H")
unsigned int Read_Sensor_Data(void)
{
	unsigned int sensordata;
	i2c_start();
	i2c_write(LIS3DH_ADR);
	i2c_write(LIS3DH_MULTI_OUT_Y_L); // (X_L+1) = X_H
	SDA_High;
	SCL_High;
	i2c_start();		
	i2c_write(LIS3DH_ADR+1); //Address plus 1 means read flag
	gsensor_value[0]=i2c_read();
	i2c_mack();
 
    gsensor_value[1]=i2c_read();
	i2c_mack();

    gsensor_value[2]=i2c_read();
	i2c_mack();

    gsensor_value[3]=i2c_read();
	i2c_mack();

    gsensor_value[4]=i2c_read();
	i2c_mack();

    gsensor_value[5]=i2c_read();
	i2c_stop();

	sample.x = (short) (gsensor_value[0] | (((unsigned short)gsensor_value[1]) << 8));
	sample.y = (short) (gsensor_value[2] | (((unsigned short)gsensor_value[3]) << 8));
	sample.z = (short) (gsensor_value[4] | (((unsigned short)gsensor_value[5]) << 8));
	 
	return sensordata;
}
