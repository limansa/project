/*
 * DESCTIPTION:
 *     pressing the button for about 5 seconds continually, and then reboot
 *     use the timer to perform this fucntion
 * */

#include <linux/module.h>   
#include <linux/string.h>    
#include <linux/fs.h>      
#include <asm/uaccess.h>
#include <linux/init.h>

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
#include<linux/timer.h>
#include<linux/kmod.h>

#include <linux/workqueue.h>

#define MY_BUTTON 23 

// text below will be seen in 'cat /proc/interrupt' command
#define MY_INT_NAME           "MyInterrupt"

// below is optional, used in more complex code, in our case, this could be
// NULL
#define MY_DEVICE_NAME    "mydevice"

//int major, ret_val;
//volatile unsigned int val;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ITtraining.com.tw");
MODULE_DESCRIPTION("A Simple GPIO Device Driver module for RaspPi");

unsigned long flags;

struct timer_list my_timer;
int reset_count = 0;

static void timer_function(unsigned long data)
{
	char    *argv[2], *envp[5];
	int button_level ;


	printk("My timer with reset count :%d\n", reset_count);
	button_level = gpio_get_value(MY_BUTTON);

	if(button_level == 0){
		if( (++reset_count) >= 5){
			// -- reset system
			printk("START to RESET SYSTEM!!!\n");
        	//argv[0] = "/home/pi/bin/QC1602A_Normal_5V.py";
        	argv[0] = "/sbin/reboot";
        	argv[1] = 0;
        	envp[0] = "HOME=/";
        	envp[1] = "PATH=/sbin:/bin:/usr/sbin:/usr/bin";
        	envp[2] = 0;
        	call_usermodehelper(argv[0], argv, envp, 0);
			printk("call_usermodehelper()\n");
			reset_count = 0;
		}else{
			mod_timer(&my_timer, jiffies + HZ );
		}

	}else{
		reset_count = 0;
	}

	return ;
}




/****************************************************************************/
/* Interrupts variables block                                               */
/****************************************************************************/

short int my_int_num = 0;

/****************************************************************************/
/* IRQ handler - fired on interrupt                                         */
/***************************************************************************/
static irqreturn_t r_irq_handler(int irq, void *dev_id, struct pt_regs *regs) 
{
	printk("my INT trigged!!!!\n");
	// reset the counter of time

	reset_count = 0;

	local_irq_save(flags);
		mod_timer(&my_timer, jiffies + HZ );
	local_irq_restore(flags);
	return IRQ_HANDLED;
}

/****************************************************************************/
/* This function configures interrupts.                                     */
/****************************************************************************/

int r_int_config(void) 
{

   // -- request button from 
   if( gpio_request(MY_BUTTON, MY_DEVICE_NAME) ) {
   	printk("error: gpio_request %s\n", MY_INT_NAME);
   	return -1;
   }


   // get the interrupt number of MY_BUTTON 
   if ( (my_int_num = gpio_to_irq(MY_BUTTON)) < 0 ) {
      printk("GPIO to IRQ mapping failure %s\n", MY_INT_NAME);
      return -1;
   }

   printk(KERN_NOTICE "Mapped int %d\n", my_int_num );

   // REQUEST the INTERRUPT
   if (request_irq( my_int_num ,
                   (irq_handler_t ) r_irq_handler,
                   IRQF_TRIGGER_FALLING,
                   MY_INT_NAME,
                   MY_DEVICE_NAME)) {
      printk("Irq Request failure\n");
      return -1;
   }


   return 0;
}


/****************************************************************************/
/* This function releases interrupts.                                       */
/****************************************************************************/
void r_int_release(void) 
{
   free_irq(my_int_num, MY_DEVICE_NAME);
   gpio_free(MY_BUTTON);

   return;
}



/*
 * INIT MODULE
 * */
int init_module(void)
{

	// -- initialize the timer 
	init_timer(&my_timer);
	my_timer.function = timer_function;
	my_timer.data = NULL;
	my_timer.expires = jiffies + HZ; 
	add_timer(&my_timer);

	if(r_int_config() < 0)
		return -1;

        return 0;
}




/*
 * CLEANUP MODULE
 * */
void cleanup_module(void)
{
	r_int_release();
}


