/*
 *  Created on: 2016¦~2¤ë5¤é
 *      Author: robot@ittraining.com.tw
 */

//#include "uart.h"

#include <bcm2835.h>
#include "it_shield.h"

int main (void)
{
   		if (!bcm2835_init())
	    return ;


           bcm2835_gpio_fsel(PWM0,BCM2835_GPIO_FSEL_ALT5); //set gpio for PWM0


           bcm2835_pwm_set_clock(1920);   //set min frequence =19.2M/1920
           bcm2835_pwm_set_mode(0,1,1);   //(channel,PWM0 MSEN enable , PWM0 enable)
           bcm2835_pwm_set_range(0,200);  //set period=20ms
	  
	
  while (1)
       {
             static int a;
	           for(a=5;a<=20;a++)
                   { 
                    bcm2835_pwm_set_data(0,a);    //set pulse width 
                  bcm2835_delay(100);
                   }
                   for(a=20;a>=5;a--)
                   { 
                    bcm2835_pwm_set_data(0,a);    //set pulse width 
                  bcm2835_delay(100);
                   }
                   
        }
     
           
    bcm2835_close();
    return 0;
}



