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

#include <linux/module.h>   
#include <linux/string.h>    
#include <linux/fs.h>      
#include <asm/uaccess.h>
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
#include <linux/platform_device.h>
#include <mach/platform.h>
#include <linux/time.h>
#include <linux/delay.h>

#include "../platdata.h"
#define MY_DUMMY_PLATFORM_DEV_NAME "joseph_dummy_device"

/* *********************************************
 * PLATFORM RESOURCE and DEVICE
 * location : arch/arm/mach-2708.c
 * *********************************************
 * */

// -- PLATFORM RESOURCES



static struct resource MY_DUMMY_resources[] = {
	{
		.start = 0x300,
		.end = 0x400,
		.flags = IORESOURCE_MEM,
		.name  = "it-mem"
	},
  {
		.start = 30, //fake
		.end = 30,
		.flags = IORESOURCE_IRQ,
  },


};

// -- PLATFORM DEVICE 

static struct clk_pdata  itpdata = {
        .clk = 100, //e.g., 100MHZ
        .num_clock = 3,
};


static struct platform_device MY_DUMMY_device = {
	.name = MY_DUMMY_PLATFORM_DEV_NAME,
	.id = 100,  //when .name is same, using .id to distgunish
	.num_resources = ARRAY_SIZE(MY_DUMMY_resources),
	.resource = MY_DUMMY_resources,
	.dev.platform_data = &itpdata,
	
};





// -- Module INIT
static int __init MY_DUMMY_init(void)
{
	return platform_device_register(&MY_DUMMY_device);
}

static void __exit MY_DUMMY_exit(void)
{
	platform_device_del(&MY_DUMMY_device);
}

module_init(MY_DUMMY_init);
module_exit(MY_DUMMY_exit);

//MODULE_DESCRIPTION("Platform device and driver example");
//MODULE_AUTHOR("ITTraining");
MODULE_LICENSE("GPL v2");
//MODULE_ALIAS("platform:" MY_DUMMY_PLATFORM_DEV_NAME);
