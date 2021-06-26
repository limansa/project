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
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/slab.h>
#include <linux/gpio.h>
//#include <linux/workqueue.h>
#include "../include/it_shield.h"

#define MY_INT_NAME "MyInterrupt"
#define MY_DEV_NAME "mydevice"

static struct gpio leds_gpios[] = {
    { LED3, GPIOF_OUT_INIT_LOW, "Green LED" }, /* default to OFF */
    { LED4, GPIOF_OUT_INIT_LOW, "Red LED"   }, /* default to OFF */
	{ BUTTON1, GPIOF_IN, MY_DEV_NAME  }, /* default to OFF */
	{ COM, GPIOF_OUT_INIT_HIGH, "COM"  }
};


struct mydev{
	struct gpio *tbl;
	int irq;
	//struct work_struct workq;
	struct tasklet_struct tasklet;
	dev_t dev;
	char dev_name[32];
	
};

struct mydev *p_dev;

//static void my_work_handler(struct work_struct * work);
static void my_tasklet_handler(unsigned long );

//DECLARE_WORK(my_work_queue, my_work_handler);
//static void my_work_handler(struct work_struct * work)
static void my_tasklet_handler(unsigned long data)
{
	static int led_trigger = 0; 
	struct mydev	*ptr;

	//ptr = container_of(work, struct mydev, workq);
	ptr = (struct mydev *) data;
	//tasklet_disable(&ptr->tasklet);
	//tasklet_disable_nosync(&ptr->tasklet);
	gpio_set_value(ptr->tbl[0].gpio, led_trigger);
	gpio_set_value(ptr->tbl[1].gpio, !led_trigger);
	led_trigger = led_trigger ? (0):(1);
	//tasklet_enable(&ptr->tasklet);
}


static irqreturn_t r_irq_handler(int irq, void *data) 
{
   unsigned long flags;
   local_irq_save(flags);
   //schedule_work(&p_dev->workq);
   tasklet_schedule(&p_dev->tasklet);
   local_irq_restore(flags);
   return IRQ_HANDLED;
}


int init_module(void)
{
	int err;

    p_dev=(struct mydev *)kmalloc(sizeof(struct mydev),GFP_KERNEL);
	
	if (p_dev==NULL) { 
	 printk("memory error!");
	 return -ENOMEM;
	}
	
	printk("*****LED GPIO Init ******************\n");
	
	p_dev->tbl=leds_gpios;
	
    if (gpio_request_array(leds_gpios, ARRAY_SIZE(leds_gpios)))  return -1;

	p_dev->irq = gpio_to_irq(p_dev->tbl[2].gpio);
	strncpy(p_dev->dev_name,p_dev->tbl[2].label,32);
	//INIT_WORK(&p_dev->workq, my_work_handler);
	tasklet_init(&p_dev->tasklet, my_tasklet_handler, (unsigned long) p_dev);

	
	if(p_dev->irq < 0) return -1;
	err = request_irq( p_dev->irq, 
			r_irq_handler, 
			IRQF_TRIGGER_RISING, 
			MY_INT_NAME, 
			MY_DEV_NAME);
	if(err ) return -1;

	return 0;
}

void cleanup_module(void)
{
	free_irq(p_dev->irq, MY_DEV_NAME);

	 gpio_set_value(p_dev->tbl[0].gpio, 0);
     gpio_set_value(p_dev->tbl[1].gpio, 0);
	 gpio_free_array (leds_gpios, ARRAY_SIZE(leds_gpios));

	//flush_scheduled_work();
	tasklet_kill(&p_dev->tasklet);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ITtraining.com.tw");
MODULE_DESCRIPTION("A Simple GPIO Device Driver module for RaspPi");
