
#ifndef __Gsensor_H
#define __Gsensor_H

#include<bcm2835.h>
#include<stdint.h>
//extern unsigned short int LIS3DH_Get_Raw(void);
void LIS3DH_Init(void);
int get_gsensor_value(void);

#endif