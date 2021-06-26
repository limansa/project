#include<stdio.h>
#include<stdlib.h>
#include<si7020.h>
#include<lib_i2c_gpio.h>
#include<bcm2835.h>


struct si7020_t * si7020_new(uint8_t i2c_addr)
{
	struct si7020_t * si;
	si = (struct si7020_t *) malloc(sizeof(struct si7020_t));
	if (si == 0) return 0;
	si->i2c_addr = i2c_addr;
	si->temperature_raw = 0;
	si->humidity_raw = 0;
	return si;
}


void si7020_free(struct si7020_t * si)
{
	free(si);
}


int si7020_measure(struct si7020_t * si)
{
	int res,i;
	uint8_t buff[3];
	res = gp_i2c_read_data_block_2(si->i2c_addr, 0xF5, buff, 3);
	if(res) return res;
	si->humidity_raw = (((uint16_t) buff[0] ) << 8 ) | (buff[1]);
	si->humidity_raw &=0x0000fffc;
	si->humi = (( ( 125.0 * (float)si->humidity_raw ) / 65535.0) - 6.0 )/100.0;

	//res = gp_i2c_read_data_block(si->i2c_addr, 0xE0, buff, 3);
	res = gp_i2c_read_data_block_2(si->i2c_addr, 0xF3, buff, 3);
	if(res) return res + 3;
	si->temperature_raw = (((uint16_t) buff[0] ) << 8 ) | (buff[1]);
	si->temperature_raw &=0x0000fffc;
	si->temp = ((175.72* (float)si->temperature_raw) / 65535.0 ) - 46.85;
	return 0;
}


float si7020_get_humi(struct si7020_t * si)
{
	return si->humi;
}




float si7020_get_temp(struct si7020_t * si)
{
	return si->temp;
}


int si7020_reset(struct si7020_t * si)
{
	return gp_i2c_send_cmd(si->i2c_addr, 0xFE);
}

