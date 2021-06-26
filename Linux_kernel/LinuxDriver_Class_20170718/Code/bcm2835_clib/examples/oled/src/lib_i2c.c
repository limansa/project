#include<stdint.h>
#include<lib_i2c.h>
#include<bcm2835.h>

void i2c_start(void)
{
    bcm2835_i2c_begin();
    bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_150);
}

uint8_t i2c_read_data_block(uint8_t i2c_addr, uint8_t reg, uint8_t * buff, uint8_t len)
{
    int res;
    bcm2835_i2c_setSlaveAddress(i2c_addr);
    res = bcm2835_i2c_write(&reg,1);
    if(res != BCM2835_I2C_REASON_OK) return res;
    res = bcm2835_i2c_read(buff, len);
    if(res != BCM2835_I2C_REASON_OK) return res;
    return BCM2835_I2C_REASON_OK;
}


uint8_t i2c_write_data_block(uint8_t i2c_addr, uint8_t reg, uint8_t * buff, uint8_t len)
{
    int res, i ;
    uint8_t _buff[len+1];

    bcm2835_i2c_setSlaveAddress(i2c_addr);
    _buff[0] = reg;
    for(i=1;i <= len ;i++) _buff[i] = buff[i-1];

    res = bcm2835_i2c_write(_buff,len+1);

    if(res != BCM2835_I2C_REASON_OK) return res;
    return BCM2835_I2C_REASON_OK;
}




// return reg value at i2ca_addr if i2c access successfully
// else return -1
int i2c_readReg(uint8_t i2c_addr, uint8_t reg)
{
    uint8_t buff;
    int res;
    res = i2c_read_data_block(i2c_addr, reg, &buff, 1);
    if(res) return -1;
    return buff;
}




// return 0 if i2c access successfully
// else return -1
int i2c_writeReg(uint8_t i2c_addr, uint8_t reg, uint8_t value)
{
    int res;
    res = i2c_write_data_block(i2c_addr, reg, &value, 1);
    if(res) return -1;
    return 0;
}





void i2c_stop(void)
{
    bcm2835_i2c_end();
}





