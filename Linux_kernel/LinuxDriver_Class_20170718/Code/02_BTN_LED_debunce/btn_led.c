/*******************************************************************************
* Copyright (c) 2015 Song Yang @ ittraining
*
* All rights reserved.
* This program is free to use, but the ban on selling behavior.
* Modify the program must keep all the original text description.
*
* Email: onionys@ittraining.com.tw
* Blog : http://blog.ittraining.com.tw
*******************************************************************************/


#include <linux/module.h>   
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#include <linux/timer.h>

#define _DEBOUNCE
#define LED 27
#define BUTTON 23
#define MY_GPIO_INT_NAME "my_button_int"
#define MY_DEV_NAME "my_device"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ITtraining.com.tw");
MODULE_DESCRIPTION("A Simple GPIO Device Driver module for RaspPi");

static short int button_irq = 0;
static unsigned long flags = 0;
static int led_trigger = 0;
struct timer_list my_timer;
static uint64_t time_stamp;
unsigned int pre_btn_level = 1;


static void timer_function(unsigned long data){
	// modify the timer for next time
	unsigned int now_btn_level;
	now_btn_level = gpio_get_value(BUTTON);
	printk("btn:%d\n", now_btn_level);

	if( ( now_btn_level == 1 ) && (pre_btn_level == 0) ){
		gpio_set_value(LED,led_trigger);
		printk("led_trigger:%d\n", led_trigger);
		led_trigger = led_trigger ? (0):(1);
	}
	pre_btn_level = now_btn_level;
}



static irqreturn_t button_isr(int irq, void *data)
{


#ifdef _DEBOUNCE
	struct timeval now_time;
	uint64_t delta_time;
	uint64_t now_time_val;

	do_gettimeofday(&now_time);
	now_time_val =((uint64_t)now_time.tv_sec * (uint64_t)1000 + (uint64_t)(now_time.tv_usec / 1000));  
    delta_time = now_time_val - time_stamp;
	if(delta_time < 20){ // < 20ms
		return IRQ_HANDLED;
	}
	printk("time_stamp = now_time_val\n");
	time_stamp = now_time_val;

	local_irq_save(flags);
	mod_timer(&my_timer, jiffies + HZ/50);
	local_irq_restore(flags);
	return IRQ_HANDLED;

#else

	local_irq_save(flags);
	printk("button_isr !!!!\n");
	gpio_set_value(LED, led_trigger);
	led_trigger = led_trigger ? (0):(1);
	local_irq_restore(flags);
	return IRQ_HANDLED;
#endif

}


int init_module(void)
{
	// -- setup the led gpio as output
	printk("module: button interrupt example.\n");
	if(gpio_is_valid(LED) < 0) return -1;
	if(gpio_request(LED, "LED") < 0) return -1;
	gpio_direction_output(LED, 0 );

	// -- setup the button gpio as input and request irq
	if(gpio_request(BUTTON,"BUTTON") < 0) return -1;
	if(gpio_is_valid(BUTTON) < 0) return -1;
	if( (button_irq = gpio_to_irq(BUTTON)) < 0 )  return -1;
#ifdef _DEBOUNCE
	if( request_irq( button_irq, button_isr ,IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, MY_GPIO_INT_NAME, MY_DEV_NAME)) return -1;
#else
	if( request_irq( button_irq, button_isr ,IRQF_TRIGGER_RISING , MY_GPIO_INT_NAME, MY_DEV_NAME)) return -1;
#endif

	// timer for debounce
	init_timer(&my_timer);
	my_timer.expires = jiffies ;
	my_timer.function = timer_function;
	my_timer.data = NULL;
	add_timer(&my_timer);
	time_stamp = 0;

	return 0;

}


void cleanup_module(void)
{
	gpio_set_value(LED, 0);
	gpio_free(LED);
	free_irq(button_irq, MY_DEV_NAME);
	gpio_free(BUTTON);
	del_timer(&my_timer);
}
