/*******************************************************************************
* Copyright (c) 2015 ittraining
*
* All rights reserved.
* This program is free to use, but the ban on selling behavior.
* Modify the program must keep all the original text description.
* Raspberry Pi Shield V3.0
* Email: service@ittraining.com.tw
* Blog : http://blog.ittraining.com.tw
* Web:  http://www.ittraining.com.tw 
*******************************************************************************/
#include <bcm2835.h>

#define LED1  5
#define LED2  6
#define COM 22
int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO
    // Use for testing
//    bcm2835_set_debug(1);

    if (!bcm2835_init())
	return 1;

    // Set the pin to be an output
    bcm2835_gpio_fsel(LED1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LED2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(COM, BCM2835_GPIO_FSEL_OUTP);
	 bcm2835_gpio_write(COM, HIGH);
    // Blink
    while (1)
    {
	// Turn it on
	bcm2835_gpio_write(LED1, HIGH);
	bcm2835_gpio_write(LED2, LOW);
	
	// wait a bit
	bcm2835_delay(200);
	
	// turn it off
	bcm2835_gpio_write(LED1, LOW);
	bcm2835_gpio_write(LED2, HIGH);
	
	// wait a bit
	bcm2835_delay(200);
    }
    bcm2835_close();
    return 0;
}

