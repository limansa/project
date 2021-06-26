#ifndef SI7020_H
#define SI7020_H

#include<stdint.h>


struct si7020_t{
	uint8_t i2c_addr;
	uint32_t temperature_raw;
	uint32_t humidity_raw;
	float temp;
	float humi;
};

struct si7020_t * si7020_new(uint8_t i2c_addr);
void si7020_free(struct si7020_t * si);

int si7020_measure(struct si7020_t * si);
float si7020_get_humi(struct si7020_t * si);
float si7020_get_temp(struct si7020_t * si);
int si7020_reset(struct si7020_t * si);

#endif
