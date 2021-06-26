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
#include <linux/string.h>    
#include <linux/init.h>
#include <linux/cdev.h>

#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/io.h>
#include <linux/sched.h>
#include <linux/interrupt.h>

#include <linux/list.h>
#include <linux/irq.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/timer.h>
#include "../include/it_shield.h"



// below is optional, used in more complex code, in our case, this could be
// NULL
#define MY_DEVICE_NAME    "myLED_timer"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ITtraining.com.tw");
MODULE_DESCRIPTION("A Simple GPIO Device Driver module for RaspPi");


struct timer_list my_timer;
int my_flag = 0;

/*
 * TIMER FUNCTION
 * */

static void timer_function(unsigned long data){
	gpio_set_value(LED0, my_flag == 1);
	gpio_set_value(LED1, my_flag == 0);
	my_flag = my_flag ? (0):(1);
	// modify the timer for next time
	mod_timer(&my_timer, jiffies + HZ /10);
}


/*
 * INIT MODULE
 * */
int init_module(void)
{

	printk("moudle: LED blinking ...\n");

	printk("*****LED GPIO Init ******************\n");
	if(gpio_request(LED0,"LED0") ) return -1;
	if(gpio_request(LED1,"LED1") ) return -1;
	if(gpio_request(COM, "COM")) return -1;
	
	gpio_direction_output(LED0, 0);
	gpio_direction_output(LED1, 0);
	gpio_direction_output(COM, 1 );

	//  -- initialize the timer 
	init_timer(&my_timer);
	my_timer.expires = jiffies + HZ ;
	my_timer.function = timer_function;
	my_timer.data = 0;

	// -- TIMER START 
	add_timer(&my_timer);

	return 0;
}




/*
 * CLEANUP MODULE
 * */
void cleanup_module(void)
{
	del_timer(&my_timer);

	printk("module : LED blinking END\n");
	gpio_set_value(LED0, 0);
	gpio_set_value(LED1, 0);
	gpio_free(LED0);
	gpio_free(LED1);		
	gpio_free(COM);
}

