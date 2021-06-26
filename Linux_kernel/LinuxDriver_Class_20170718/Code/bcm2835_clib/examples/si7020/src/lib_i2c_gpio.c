#define LIB_I2C_GPIO_C

#include<stdio.h>
#include<lib_i2c_gpio.h>
#include<unistd.h>
#include<bcm2835.h>
#include<stdint.h>
#include<time.h>

static struct timespec d1us;

#define W_BIT 0x00
#define R_BIT 0x01

void gp_i2c_start(uint8_t sda_p, uint8_t scl_p)
{
	sda_pin = sda_p;
	scl_pin = scl_p;
	SDA_AS_OUT();
	SCL_AS_OUT();
	SDA_UP();
	SCL_UP();
	usleep(10);
}


int gp_i2c_read_data_block(uint8_t i2c_addr,uint8_t reg, uint8_t * buff, uint8_t len )
{
	uint8_t i;
	SDA_AS_OUT();
	SCL_AS_OUT();

	S_bit();
	send_byte( (i2c_addr << 1) | W_BIT );
	if(is_ACK() == 0) return 1;

	send_byte( reg );
	if(is_ACK() == 0) return 2;

	//P_bit();
	usleep(100);
	S_bit();

	send_byte( (i2c_addr << 1) | R_BIT );
	if(is_ACK() == 0) return 3;

	len--;
	for(i = 0; i < len ; i++){
		buff[i] = read_byte();
		send_ACK();
	}

	buff[len] = read_byte();

	usleep(1);
	send_NACK();
	usleep(1);
	P_bit();
	usleep(100);
	return 0;
}





int gp_i2c_read_data_block_2(uint8_t i2c_addr,uint8_t reg, uint8_t * buff, uint8_t len )
{
	uint8_t i;
	SDA_AS_OUT();
	SCL_AS_OUT();

	S_bit();
	send_byte( (i2c_addr << 1) | W_BIT );
	if(is_ACK() == 0) return 1;

	send_byte( reg );
	if(is_ACK() == 0) return 2;

	//P_bit();
	usleep(100000);
	S_bit();

	send_byte( (i2c_addr << 1) | R_BIT );
	if(is_ACK() == 0) return 3;

	len--;
	
	for(i = 0; i < len ; i++){
		buff[i] = read_byte();
		send_ACK();
	}

	buff[len] = read_byte();

	usleep(1);
	send_NACK();
	usleep(1);
	P_bit();
	usleep(100);
	return 0;
}




int gp_i2c_write_data_block(uint8_t i2c_addr,uint8_t reg, uint8_t * buff, uint8_t len )
{
	uint8_t i;
	SDA_AS_OUT();
	SCL_AS_OUT();
	S_bit();

	send_byte( (i2c_addr << 1) | W_BIT );
	if(is_ACK() == 0) return 1;

	send_byte( reg );
	if(is_ACK() == 0) return 2;

	for(i = 0; i < len ; i++){
		send_byte( buff[i] );
		if(is_ACK() == 0) return 3;
	}

	usleep(1);
	P_bit();
	usleep(100);
	return 0;
}



int gp_i2c_readReg(uint8_t i2c_addr, uint8_t reg)
{
	return 0;
}



int gp_i2c_writeReg(uint8_t i2c_addr, uint8_t reg, uint8_t value)
{
	return 0;
}








static void write_bit(uint8_t bit)
{
	if(bit)
		SDA_UP();
	else
		SDA_DOWN();
	usleep(1);
	SCL_UP();
	usleep(1);
	SCL_DOWN();
	usleep(1);
	
}




static uint8_t read_bit()
{
	uint8_t res;

	usleep(1);
	SCL_UP();
	usleep(1);
	res = SDA_READ_IN();
	SCL_DOWN();
	//SDA_AS_OUT();
	
	return res;
}




static void send_byte(uint8_t byte)
{
	SCL_AS_OUT();
	SDA_AS_OUT();

	//SCL_DOWN();

	//SDA_UP();
	usleep(1);
	write_bit( ((struct B8*)(&byte))->b7 );
	write_bit( ((struct B8*)(&byte))->b6 );
	write_bit( ((struct B8*)(&byte))->b5 );
	write_bit( ((struct B8*)(&byte))->b4 );
	write_bit( ((struct B8*)(&byte))->b3 );
	write_bit( ((struct B8*)(&byte))->b2 );
	write_bit( ((struct B8*)(&byte))->b1 );
	write_bit( ((struct B8*)(&byte))->b0 );
	SDA_UP();

}




static uint8_t read_byte()
{
	uint8_t byte;
	SCL_DOWN();
	SDA_UP();
	SDA_AS_IN();
	SDA_IN_PULL_HIGH();
	((struct B8 *)(&byte))->b7 = read_bit();
	((struct B8 *)(&byte))->b6 = read_bit();
	((struct B8 *)(&byte))->b5 = read_bit();
	((struct B8 *)(&byte))->b4 = read_bit();
	((struct B8 *)(&byte))->b3 = read_bit();
	((struct B8 *)(&byte))->b2 = read_bit();
	((struct B8 *)(&byte))->b1 = read_bit();
	((struct B8 *)(&byte))->b0 = read_bit();
	SDA_AS_OUT();
	return byte;
}




static void S_bit()
{
	SDA_UP();
	SCL_UP();
	usleep(10);
	SDA_DOWN();
	usleep(1);
	SCL_DOWN();
	usleep(1);
}




static void P_bit()
{
	SDA_AS_OUT();
	SDA_DOWN();
	SCL_DOWN();
	usleep(1);
	SCL_UP();
	usleep(1);
	SDA_UP();
	usleep(1);
}




static int is_ACK()
{
	int res;
	SDA_UP();
	SDA_AS_IN();
	SDA_IN_PULL_HIGH();
	usleep(10);
	SCL_UP();
	usleep(10);
	res = SDA_READ_IN();
	SCL_DOWN();
	usleep(1);
	SDA_AS_OUT();
	SDA_UP();
	if(res == 0) 
		return 1;
	return 0;
}



static int send_ACK()
{
	SDA_AS_OUT();
	SDA_DOWN();
	usleep(1);
	SCL_UP();
	usleep(1);
	SCL_DOWN();
	SDA_UP();
	SDA_AS_IN();
	usleep(1);
	return 0;
}




static send_NACK()
{
	SDA_AS_OUT();
	SDA_UP();
	SCL_UP();
	usleep(1);
	SCL_DOWN();
	usleep(1);
	SDA_UP();
	usleep(1);
	SDA_AS_IN();

	return 0;
}





int gp_i2c_send_cmd(uint8_t i2c_addr,uint8_t cmd )
{
	uint8_t i;
	SDA_AS_OUT();
	SCL_AS_OUT();

	S_bit();
	send_byte( (i2c_addr << 1) | W_BIT );
	if(is_ACK() == 0) return 1;

	send_byte( cmd );
	if(is_ACK() == 0) return 2;

	P_bit();

	usleep(100);
	return 0;
}


