/*******************************************************************************
* Copyright (c) 2015 ittraining
*
* All rights reserved.
* This program is free to use, but the ban on selling behavior.
* Modify the program must keep all the original text description.
*
* Email: service@ittraining.com.tw
* Blog : http://blog.ittraining.com.tw
* Web:  http://www.ittraining.com.tw 
*******************************************************************************/


#include <linux/module.h>   
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#include "../include/it_shield.h"

#define MY_GPIO_INT_NAME "my_button_int"
#define MY_DEV_NAME "it_device"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ITtraining.com.tw");
MODULE_DESCRIPTION("A Simple GPIO Device Driver module for RaspPi");

static short int button_irq = 0;
static unsigned long flags = 0;
static int led_trigger = 0;

static irqreturn_t button_isr(int irq, void *data)
{
	int val = 0;
	local_irq_save(flags);
	printk("button_isr !!!!\n");
	gpio_set_value(BUZZER, led_trigger);
	val = gpio_get_value(BUTTON1);
	printk("get value : %d \n", val);
	led_trigger = led_trigger ? (0):(1);
	local_irq_restore(flags);
	return IRQ_HANDLED;
}


int init_module(void)
{
	// -- setup the led gpio as output
	printk("module: button interrupt example.\n");
	if(!gpio_is_valid(BUZZER)) return -1;
	if(gpio_request(BUZZER, "BUZZER")) return -1;
	gpio_direction_output(BUZZER, 0 );
	
	if(!gpio_is_valid(COM)) return -1;
	gpio_direction_output(COM, 1 );

	// -- setup the button gpio as input and request irq
	if(!gpio_is_valid(BUTTON1)) return -1;
	if(gpio_request(BUTTON1,"BUTTON1")) return -1;

	if( (button_irq = gpio_to_irq(BUTTON1)) < 0 )  return -1;
	if( request_irq( button_irq, button_isr ,IRQF_TRIGGER_FALLING, MY_GPIO_INT_NAME, MY_DEV_NAME)) return -1;
	return 0;

}


void cleanup_module(void)
{
	gpio_set_value(BUZZER, 0);
	gpio_free(BUZZER);
	free_irq(button_irq, MY_DEV_NAME);
	gpio_free(BUTTON1);
	gpio_free(COM);
}
