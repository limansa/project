#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<bcm2835.h>
#include<lib_i2c_gpio.h>
#include<si7020.h>

#define SDA_PIN RPI_BPLUS_GPIO_J8_03
#define SCL_PIN RPI_BPLUS_GPIO_J8_05

int main(int argc,char *argv[]){
	int i,res;
	int i2c_addr;
	uint8_t buff[5];
	uint16_t temp_raw;
	uint32_t humi_raw;
	for(i=0 ;i<5 ;i++ ) buff[i] = 0;

	bcm2835_init();
	gp_i2c_start(SDA_PIN, SCL_PIN);

	struct si7020_t * si = si7020_new(0x40);

	//res = si7020_reset(si);
	//printf("cmd reset res:%d\n", res);
	//usleep(1000000);
	
	for(i=0 ;i<65535 ;i){
		res = si7020_measure(si);
		printf("res:%d\n", res);
		printf("humidity: %f \n", si7020_get_humi(si));
		printf("temperature: %f \n", si7020_get_temp(si));
		usleep(500000);
	}
	
	bcm2835_gpio_fsel(RPI_BPLUS_GPIO_J8_03, BCM2835_GPIO_FSEL_ALT0);
	bcm2835_gpio_fsel(RPI_BPLUS_GPIO_J8_05, BCM2835_GPIO_FSEL_ALT0);

	return 0;
}
