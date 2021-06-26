    #include "gpio_ini.h"
    #include <bcm2835.h>
    #include "Gsensor.h"

void gpio_init(void) {
// Set the pin to be an output

    bcm2835_gpio_fsel(LED1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LED2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LED3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LED4, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LED5, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RELAY, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(BUZZER, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(COM, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(IR, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(SCL, BCM2835_GPIO_FSEL_OUTP);
    
    bcm2835_gpio_fsel(SW1, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(SW2, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(DIP1, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(DIP2, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(IRM, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(SDA, BCM2835_GPIO_FSEL_OUTP);
    
    SDA_High;SCL_High;
    
    LED1_OFF;LED2_OFF;LED3_OFF;LED4_OFF;LED5_OFF;
    bcm2835_gpio_write(COM, HIGH);
}
