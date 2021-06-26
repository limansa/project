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

#include <linux/kernel.h>
#include <linux/module.h>   
#include <asm/uaccess.h>
#include <linux/fs.h>      
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/workqueue.h>
#include <linux/version.h>

#include "../include/it_shield.h"

#define MY_MAJOR 201
#define MY_MINOR 0
#define MY_DEV_COUNT 1

#define MY_DEV_NAME "my_blocking_io_dev"
#define MY_INT_NAME "my_blocking_io_int"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ITtraining.com.tw");
MODULE_DESCRIPTION("A Simple Blocking IO device RaspPi");

static int     my_open( struct inode *, struct file * );
static ssize_t my_read( struct file * ,        char *  , size_t, loff_t *);
static ssize_t my_write(struct file * , const  char *  , size_t, loff_t *);
static int     my_close(struct inode *, struct file * );

struct file_operations my_fops = {
        read    :       my_read,
        write   :       my_write,
        open    :       my_open,
        release :       my_close,
        owner   :       THIS_MODULE
};

struct cdev my_cdev;
static char   *msg=NULL;
unsigned long flags;
short int     my_button_irq_no = 0;

static wait_queue_head_t my_wait_queue;
static int wait_queue_flag = 0;



static irqreturn_t my_irq_handler(int irq, void *data) 
{
	local_irq_save(flags);
	
	if(msg != NULL){
	    strncpy(msg,"hello\n",7);
		printk("msg is READY!\n");
	}else
		printk("msg space is NULL!!!!\n");
	wait_queue_flag = 1 ;
	wake_up_interruptible(&my_wait_queue);
	


	local_irq_restore(flags);
	return IRQ_HANDLED;
}

void my_interrupt_config(void){
	// -- request the button gpio 
   if (gpio_request( BUTTON1, MY_INT_NAME)) {
      printk("GPIO request failure: %s\n", MY_INT_NAME);
      return;
   }

   // -- get the interrupt number of this button
   if ( (my_button_irq_no = gpio_to_irq( BUTTON1 )) < 0 ) {
      printk("GPIO to IRQ mapping failure %s\n", MY_INT_NAME);
      return;
   }

   // -- register the interrupt depending on this button
	if (request_irq(my_button_irq_no,
				(irq_handler_t ) my_irq_handler,
				IRQF_TRIGGER_RISING,
				MY_INT_NAME,
				MY_DEV_NAME)) {
		printk("Irq Request failure\n");
		return;
	}

   return ;
}


void my_interrupt_release(void){
	printk("Start interrupt release\n");

	wake_up_interruptible(&my_wait_queue);

	// -- release the interrupt
	free_irq(my_button_irq_no , MY_DEV_NAME);

	// -- release the gpio of button 
	gpio_free(BUTTON1);

	printk("exit interrupt release\n");
   return;
}




// -- MODULE START
int init_module(void)
{

	int err;
	dev_t devno;
	unsigned int count = MY_DEV_COUNT;

	printk("setup char device \n");
	// -- register device number  
	devno = MKDEV(MY_MAJOR, MY_MINOR);
	register_chrdev_region(devno, MY_DEV_COUNT , MY_DEV_NAME);

        cdev_init(&my_cdev, &my_fops);
	my_cdev.owner = THIS_MODULE;
	err = cdev_add(&my_cdev, devno, count);
	
	// -- setup GPIO for button
	msg          = (char *)kmalloc(32, GFP_KERNEL);
	if (msg !=NULL)
		printk("malloc allocator address: 0x%p\n", msg);

	// -- initialize the WAIT QUEUE head
	init_waitqueue_head(& my_wait_queue);

	// -- setup the INTERRUPT
	my_interrupt_config();
	
	// -- other handle
	if (err < 0)
	{
		printk("Device Add Error\n");
		return -1;
	}

	printk("'mknod /dev/myBR_file c %d 0'.\n", MY_MAJOR);
        return 0;
}

// -- MODULE END
void cleanup_module(void)
{
	dev_t devno;
	gpio_free(BUTTON1);
	free_irq(my_button_irq_no, MY_DEV_NAME);

	devno = MKDEV(MY_MAJOR, MY_MINOR);
	unregister_chrdev_region(devno,MY_DEV_COUNT);
	cdev_del(&my_cdev);
}



static int my_open(struct inode *inod, struct file *filp)
{
	int major;
	int minor;

	major = imajor(inod);
	minor = iminor(inod);
	printk("\n*****Some body is opening me at major %d  minor %d*****\n",major, minor);

	return 0;
}


static int my_close(struct inode *inod, struct file *filp)
{
	int major, minor;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,19,0)
	major = MAJOR(filp->f_inode->i_rdev);
	minor = MINOR(filp->f_inode->i_rdev);
#else
	major = MAJOR(filp->f_dentry->d_inode->i_rdev);
	minor = MINOR(filp->f_dentry->d_inode->i_rdev);
#endif
	printk("*****Some body is closing me at major %d*****\n",minor);

	return 0;
}

static ssize_t my_read(struct file *filp, char *buff, size_t len, loff_t *off)
{
	int major, minor;
    int ret;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,19,0)
	major = MAJOR(filp->f_inode->i_rdev);
	minor = MINOR(filp->f_inode->i_rdev);
#else
	major = MAJOR(filp->f_dentry->d_inode->i_rdev);
	minor = MINOR(filp->f_dentry->d_inode->i_rdev);
#endif

	/*
	 * NON_BLOCKING I/O
	 * */
	if(filp->f_flags & O_NONBLOCK){
		return -EAGAIN;
	}

	/*
	 * BLOCKING I/O 
	 * */
	printk("Please Wait Here for Data READY.\n");
	printk("I want to sleep....ZZZZZzzzzz.....!\n");

	if (*off!=0) return 0; //for cat /dev/myBR_file

	wait_queue_flag = 0;
	
        if (wait_event_interruptible(my_wait_queue, wait_queue_flag)) {
               // return -ERESTARTSYS;
                  return -EINTR;

                       ;
      }
	

	printk("!!? Someone WAKEUP Me, because of data ready.");
	
	
	
	len=(len>7)?7:len;
       *off+=len;
	ret=copy_to_user(buff, msg, len);

	return len;
}


static ssize_t my_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
	short count;
	memset(msg, 0, 100);
	count = copy_from_user( msg, buff, len );
	return len;
}
