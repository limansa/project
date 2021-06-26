/*
  GPIO_INPUT example For raspberry pi 3
  WebSite : www.ittraining.com.tw  
  Programmer: robot@ittraining.com.tw
*/
#include <bcm2835.h>
#include <stdio.h>
 

#define LED1  5
#define LED2  13
#define GPIO_INPUT 26
#define COM 22
int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO

    int value;
    if (!bcm2835_init())
	return 1;

    // Set the pin to be an output
    bcm2835_gpio_fsel(LED1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LED2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(GPIO_INPUT, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(COM, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(COM, HIGH);
    // Blink
	
    while (1)
    {
		
	 value= bcm2835_gpio_lev(GPIO_INPUT);
	 printf("read from GPIO_INPUT: %d\n", value);	
		
	if (value==1) {	
	// Turn it on
	bcm2835_gpio_write(LED1, HIGH);
	bcm2835_gpio_write(LED2, HIGH);

	
    } else {
	
	// turn it off
	bcm2835_gpio_write(LED1, LOW);
	bcm2835_gpio_write(LED2, LOW);


    }
	
	bcm2835_delay(500);  //500ms
	}
    bcm2835_close();
    return 0;
}

