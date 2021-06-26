#ifndef LIB_I2C_GPIO_H
#define LIB_I2C_GPIO_H

#include<bcm2835.h>
#include<stdint.h>

#ifndef LIB_I2C_GPIO_C
	extern uint8_t sda_pin;
	extern uint8_t scl_pin;
#else 
	uint8_t sda_pin;
	uint8_t scl_pin;
#endif 



#define SDA_UP()   bcm2835_gpio_write(sda_pin,HIGH)
#define SDA_DOWN() bcm2835_gpio_write(sda_pin,LOW)
#define SCL_UP()   bcm2835_gpio_write(scl_pin,HIGH)
#define SCL_DOWN() bcm2835_gpio_write(scl_pin,LOW)

#define SDA_AS_OUT() bcm2835_gpio_fsel(sda_pin,BCM2835_GPIO_FSEL_OUTP)
#define SCL_AS_OUT() bcm2835_gpio_fsel(scl_pin,BCM2835_GPIO_FSEL_OUTP)
#define SDA_AS_IN() bcm2835_gpio_fsel(sda_pin,BCM2835_GPIO_FSEL_INPT)
#define SCL_AS_IN() bcm2835_gpio_fsel(scl_pin,BCM2835_GPIO_FSEL_INPT)

#define SDA_IN_PULL_HIGH() bcm2835_gpio_set_pud(sda_pin, BCM2835_GPIO_PUD_UP)
#define SDA_IN_PULL_DOWN() bcm2835_gpio_set_pud(sda_pin, BCM2835_GPIO_PUD_DOWN)
#define SCL_IN_PULL_HIGH() bcm2835_gpio_set_pud(scl_pin, BCM2835_GPIO_PUD_UP)
#define SCL_IN_PULL_DOWN() bcm2835_gpio_set_pud(scl_pin, BCM2835_GPIO_PUD_DOWN)

#define SDA_READ_IN() bcm2835_gpio_lev(sda_pin)
#define SCL_READ_IN() bcm2835_gpio_lev(scl_pin)

void gp_i2c_start(uint8_t sda_pin, uint8_t scl_pin);
int gp_i2c_read_data_block(uint8_t i2c_addr,uint8_t reg, uint8_t * buff, uint8_t len );
int gp_i2c_write_data_block(uint8_t i2c_addr,uint8_t reg, uint8_t * buff, uint8_t len );
int gp_i2c_read_data_block_2(uint8_t i2c_addr,uint8_t reg, uint8_t * buff, uint8_t len );
int gp_i2c_readReg(uint8_t i2c_addr, uint8_t reg);
int gp_i2c_writeReg(uint8_t i2c_addr, uint8_t reg, uint8_t value);


struct B8{
	unsigned b0:1;
	unsigned b1:1;
	unsigned b2:1;
	unsigned b3:1;
	unsigned b4:1;
	unsigned b5:1;
	unsigned b6:1;
	unsigned b7:1;
};




static void    S_bit();
static void    P_bit();
static int     is_ACK();
static int     send_ACK();
static int     send_NACK();
static uint8_t read_bit();

static void    send_byte(uint8_t byte);
static uint8_t read_byte();

int gp_i2c_send_cmd(uint8_t i2c_addr,uint8_t cmd );




#endif 
