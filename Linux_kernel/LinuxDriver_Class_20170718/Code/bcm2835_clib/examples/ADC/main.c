#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdint.h>
#include<mcp3008.h>


#define SPI_CS 0

int main(int argc, char **argv)
{
    int i;
	printf("bcm2835_init()\n");
	bcm2835_init();
	printf("bcm2835_spi_begin()\n");
    bcm2835_spi_begin();
    
	printf("loop start\n");
	while(i<300) {
    printf("%d\n", MCP3008_analog_read( SPI_CS , atoi(argv[1]) ));
     usleep(10000);
	 i++;
    }

	printf("loop stop\n");
    bcm2835_spi_end();
    bcm2835_close();
    return 0;
}



