

#ifndef __gpio_ini_H
#define __gpio_ini_H

#include<bcm2835.h>
#include<stdint.h>

#define RELAY  27
#define BUZZER  16
#define COM  22  
#define LED1	5 
#define LED2  6 
#define LED3  13 
#define LED4  26 
#define LED5  12
#define DIP1  20 
#define DIP2  21 
#define SW1  24 
#define SW2  23
#define IR  25
#define IRM  17
#define SDA  2
#define SCL  3

#define LED1_ON  bcm2835_gpio_write(LED1, HIGH)
#define LED2_ON  bcm2835_gpio_write(LED2, HIGH)
#define LED3_ON  bcm2835_gpio_write(LED3, HIGH)
#define LED4_ON  bcm2835_gpio_write(LED4, HIGH)
#define LED5_ON  bcm2835_gpio_write(LED5, HIGH)
#define LED1_OFF  bcm2835_gpio_write(LED1, LOW)
#define LED2_OFF  bcm2835_gpio_write(LED2, LOW)
#define LED3_OFF  bcm2835_gpio_write(LED3, LOW)
#define LED4_OFF  bcm2835_gpio_write(LED4, LOW)
#define LED5_OFF  bcm2835_gpio_write(LED5, LOW)

#define RELAY_ON  bcm2835_gpio_write(RELAY, HIGH)
#define RELAY_OFF bcm2835_gpio_write(RELAY, LOW)

#define BUZZER_ON  bcm2835_gpio_write(BUZZER, HIGH)
#define BUZZER_OFF bcm2835_gpio_write(BUZZER, LOW)

#define IR_ON  bcm2835_gpio_write(IR, HIGH)
#define IR_OFF bcm2835_gpio_write(IR, LOW)


#define SDA_High  bcm2835_gpio_write(SDA, HIGH)
#define SDA_Low   bcm2835_gpio_write(SDA, LOW)
#define SCL_High  bcm2835_gpio_write(SCL, HIGH)
#define SCL_Low   bcm2835_gpio_write(SCL, LOW)

//#define SDA_I   bcm2835_gpio_fsel(SDA, BCM2835_GPIO_FSEL_INPT);
//#define SDA_O   bcm2835_gpio_fsel(SDA, BCM2835_GPIO_FSEL_OUPT);

#endif


