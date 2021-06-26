#include "I2C_Profile.h"
#include "Gsensor.h"
#include <bcm2835.h>
#include "gpio_ini.h"
#include <stdio.h>
//============================================//
//				   LIS3DH Init
//============================================//
void LIS3DH_Init(void)
{
		i2c_write_data(LIS3DH_ADR,CTRL_REG1,0xA7); //100Hz ¡A x,y,z enable
		i2c_write_data(LIS3DH_ADR,CTRL_REG2,0x00);
		i2c_write_data(LIS3DH_ADR,CTRL_REG3,0x00);
		i2c_write_data(LIS3DH_ADR,CTRL_REG4,0x00); //Full scale selection:2g
		i2c_write_data(LIS3DH_ADR,CTRL_REG5,0x00);
		i2c_write_data(LIS3DH_ADR,CTRL_REG6,0x00);
		i2c_write_data(LIS3DH_ADR,0x32,0x00);
		i2c_write_data(LIS3DH_ADR,0x33,0x00);
		i2c_write_data(LIS3DH_ADR,0x30,0x00);
        
}

//============================================//
//		    Gsensor_Button_Led_Ctrl 
//============================================//
int get_gsensor_value(void)
{
		unsigned char sensor_avg=0;
		//sensor_avg = Read_Sensor_Data(); // Read sensor data
		return sensor_avg;

}
