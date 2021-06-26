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

/*
 * DESCRIIPT:
 *     Perform the async notification mechanism.
 *     press the button to triggle an interrupt to send a signal
 *     to registered opened file .
 *
 * */

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
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/version.h>

#include "../include/it_shield.h"

#define MY_MAJOR	200
#define MY_MINOR	0


// text below will be seen in 'cat /proc/interrupt' command
#define MY_INT_NAME "MyInterrupt"

// below is optional, used in more complex code, in our case, this could be
// NULL
#define MY_DEV_NAME "mydevice"

volatile unsigned int val;


static int     my_open( struct inode *, struct file *);
static int     my_close(struct inode *, struct file *);
static ssize_t my_read( struct file *, char *      , size_t, loff_t *);
static ssize_t my_write(struct file *, const char *, size_t, loff_t *);
static int     my_fasync(int fd, struct file * flip, int mode);
static struct fasync_struct * my_async_list = NULL;


/////////////////////////////////////////////
static void my_tasklet_handler(unsigned long );
/////////////////////////////////////////////

static char   *msg=NULL;
unsigned long flags;

struct file_operations my_fops = {
        read    :       my_read,
        write   :       my_write,
        open    :       my_open,
        release :       my_close,
		fasync  :       my_fasync,
        owner   :       THIS_MODULE,
        };

struct cdev my_cdev;

/****************************************************************************/
/* Interrupts variables block                                               */
/****************************************************************************/
short int my_int_num    = 0;


////////////////////////////////////////////////////////////////
DECLARE_TASKLET(mytasklet, my_tasklet_handler, 0);

static void my_tasklet_handler(unsigned long flag)
{

   printk("==== TASKLET HANDLER : \n");

	msg[0] = 'H';
	msg[1] = 'E';
	msg[2] = 'L';
	msg[3] = 'L';
	msg[4] = 'O';
	msg[5] = '\0';
   //tasklet_disable(&mytasklet);
   tasklet_disable_nosync(&mytasklet);
   kill_fasync(&my_async_list , SIGIO, POLL_IN);
   tasklet_enable(&mytasklet);   
}

/****************************************************************************/
/* IRQ handler - fired on interrupt                                         */
/***************************************************************************/

static irqreturn_t r_irq_handler(int irq, void *dev_id, struct pt_regs *regs) 
{
   printk("==== INT HANDLER : schedule mytasklet \n");
   // disable hard interrupts (remember them in flag 'flags')
	if(my_async_list != 0){
		local_irq_save(flags);
		tasklet_schedule(&mytasklet);
		local_irq_restore(flags);
		return IRQ_HANDLED;
   }else{
	   return IRQ_HANDLED;
   }
}

/****************************************************************************/
/* This function configures interrupts.                                     */
/****************************************************************************/

void r_int_config(void) 
{
   if (gpio_request(BUTTON1, MY_INT_NAME)) {
      printk("GPIO request failure: %s\n", MY_INT_NAME);
      return;
   }

   if ( (my_int_num = gpio_to_irq(BUTTON1)) < 0 ) {
      printk("GPIO to IRQ mapping failure %s\n", MY_INT_NAME);
      return;
   }

   printk(KERN_NOTICE "Mapped int %d\n", my_int_num);

   //////////////////////////////////////////////////////////
   // REQUEST IRQ
   //////////////////////////////////////////////////////////
   if (request_irq(my_int_num,
                   (irq_handler_t ) r_irq_handler,
                   IRQF_TRIGGER_RISING,
                   MY_INT_NAME,
                   MY_DEV_NAME)) {
      printk("Irq Request failure\n");
      return;
   }
   //////////////////////////////////////////////////////////

   return;
}


/****************************************************************************/
/* This function releases interrupts.                                       */
/****************************************************************************/
void r_int_release(void) {

   printk("==== INT RELEASE : \n");
   free_irq(my_int_num, MY_DEV_NAME);
   gpio_free(BUTTON1);

   return;
}


/*
 * MODULE: INIT 
 * */
int init_module(void)
{

	dev_t devno;
	unsigned int count;
	int err;

	printk("<1> Hello World, device %s INIT\n", MY_DEV_NAME);

	devno = MKDEV(MY_MAJOR, MY_MINOR);
	register_chrdev_region(devno, 1, "mydevice");

        cdev_init(&my_cdev, &my_fops);

	my_cdev.owner = THIS_MODULE;
        count = 1;
	err = cdev_add(&my_cdev, devno, count);
	printk("'mknod /dev/mydevice c %d 0'.\n", MY_MAJOR);

	msg 	     = (char *)kmalloc(32, GFP_KERNEL);
	if (msg !=NULL)
		printk("malloc allocator address: 0x%p\n", msg);
	
	
	printk("==== BUTTON GPIO Init\n");
	
	if (err < 0)
	{
		printk("Device Add Error\n");
		return -1;
	}

	// -- interrupt configure
	printk("==== INTERRUPT INIT !\n");
	r_int_config();
        return 0;
}


/*
 * MODULE: EXIT
 * */
void cleanup_module(void)
{
	dev_t devno;
	devno = MKDEV(MY_MAJOR, MY_MINOR);
	r_int_release();
	if (msg){
        /* release the malloc */
        kfree(msg);
	}
	tasklet_kill(&mytasklet);
	unregister_chrdev_region(devno, 1);
	cdev_del(&my_cdev);
}




/*************************************************/
/* FILE OPERATION : OPEN READ WRITE CLOSE FASYNC */
/*************************************************/

/*
 * FILE OPERATION: OPEN
 * */
static int my_open(struct inode *inod, struct file *fil)
{

	int major;
	int minor;

	major = imajor(inod);
	minor = iminor(inod);
	printk("\n*****Some body is opening me at major %d  minor %d*****\n",major, minor);
	return 0;
}




/*
 * FILE OPERATION: READ
 * */
static ssize_t my_read(struct file *filp, char *buff, size_t len, loff_t *off)
{
	printk("==== FILE OPERATION: READ \n");
	printk("copy_to_user: %s\n", msg);
	return copy_to_user(buff, msg, 5);
}




/*
 * FILE OPERATION: WRITE
 * */
static ssize_t my_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
	
	int major,minor;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,19,0)
	major = MAJOR(filp->f_inode->i_rdev);
	minor = MINOR(filp->f_inode->i_rdev);
#else
	major = MAJOR(filp->f_dentry->d_inode->i_rdev);
	minor = MINOR(filp->f_dentry->d_inode->i_rdev);
#endif
	memset(msg, 0, 32);
        printk("==== FILE OPERATION: WRITE : major=%d\n",major);

	return len;
}




/*
 * FILE OPERATION: CLOSE
 * */
static int my_close(struct inode *inod, struct file *filp)
{
	
	int major,minor;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,19,0)
	major = MAJOR(filp->f_inode->i_rdev);
	minor = MINOR(filp->f_inode->i_rdev);
#else
	major = MAJOR(filp->f_dentry->d_inode->i_rdev);
	minor = MINOR(filp->f_dentry->d_inode->i_rdev);
#endif
	printk("*****Some body is closing me at major %d*****\n",major);

	// -- remove the pid of current process from my_async_list
	my_fasync(-1, filp, 0);

		return 0;
}




/*
 * FILE OPERATION: FASYNC
 * */
static int my_fasync(int fd, struct file * flip, int mode)
{
	printk("FILE OPERATION: FASYNC \n" );
	return fasync_helper(fd, flip, mode, &my_async_list); 
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("ITtraining.com.tw");
MODULE_DESCRIPTION("A Simple GPIO Device Driver module for RaspPi");
