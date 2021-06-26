#include<mcp3008.h>
#include<bcm2835.h>


int MCP3008_analog_read(uint8_t chip_select, uint8_t analog_ch)
{
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536);

	if(chip_select == 0){
        bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
        bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
	}
	else if(chip_select == 1){
        bcm2835_spi_chipSelect(BCM2835_SPI_CS1);
        bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, LOW);
	}

    uint8_t buff[]={0x01, 0x00,0x00};

	if(analog_ch >= 0 && analog_ch <=7){
		buff[1] = ( 8 + analog_ch ) << 4;
        bcm2835_spi_transfern(buff,3);
		int val = (((uint16_t)buff[1] & 0x0007) << 8) + ( (uint16_t) buff[2] );
		return val;
	}
	return -1;
}

