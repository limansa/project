#ifndef MCP3008_H
#define MCP3008_H

#include<bcm2835.h>
#include<stdint.h>

int MCP3008_analog_read(uint8_t chip_select, uint8_t analog_ch);

#endif 
