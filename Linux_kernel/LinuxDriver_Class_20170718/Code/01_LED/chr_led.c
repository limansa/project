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
/*
 * DESCRIPTION:
 *     a simple example of char device 
 *     this char device can control the GPIO by file operation : write
 *     to write specific message as command
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


#define MY_MAJOR  200
#define MY_MINOR  0
#define MY_DEV_COUNT 2
#define MY_CLASS_NAME "myLED_class"
#define MY_NODE_NAME1   "myLED0"
#define MY_NODE_NAME2   "myLED1"

#define MY_DEV_NAME "myLED"



static long  my_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static int     my_open( struct inode *, struct file * );
static ssize_t my_read( struct file * ,        char *  , size_t, loff_t *);
static ssize_t my_write(struct file * , const  char *  , size_t, loff_t *);
static int     my_close(struct inode *, struct file * );

struct file_operations my_fops = {
        read    :       my_read,
        write   :       my_write,
        open    :       my_open,
        release :       my_close,
        unlocked_ioctl :  my_ioctl,
        owner   :       THIS_MODULE
};

static char   *msg=NULL;
struct cdev my_cdev;
static struct class *my_class;



/*
 * INIT_MODULE -- MODULE START --
 * */
 
 
static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{

    printk("cmd=%ud,arg=%lu\n",cmd,arg);
  	switch(cmd){
		case 0: //LED0
		   	gpio_set_value(LED0,(arg==0)?0:1);
			break;
		case 1: //LED1
      	gpio_set_value(LED1,(arg==0)?0:1);
			break;
		default:
	     return -EINVAL;
	}

        return 0;
}

int led_init_module(void)
{

	dev_t devno;
	unsigned int count = MY_DEV_COUNT; // apply for two minor for two LED
	int err;

	devno = MKDEV(MY_MAJOR, MY_MINOR);
	register_chrdev_region(devno, count , MY_DEV_NAME);

	// -- initial the char device 
	cdev_init(&my_cdev, &my_fops);
	my_cdev.owner = THIS_MODULE;
	err = cdev_add(&my_cdev, devno, count);

	if (err < 0)
	{
		printk("Device Add Error\n");
		return -1;
	}

	// -- print message 
	//printk("<1> Hello World. This is myLED Driver.\n");
	//printk("'mknod /dev/myLED0 c %d 0'.\n", MY_MAJOR);
	//printk("'mknod /dev/myLED1 c %d 1'.\n", MY_MAJOR);
	// udev create file node in file system
	//     -- MY_CLASS_NAME reveals in /sys/class/
	my_class = class_create(THIS_MODULE, MY_CLASS_NAME); 
	if(IS_ERR(my_class)){
		printk("error at class_create()\n");
		return -1;
	}
	device_create(my_class, NULL, MKDEV(MY_MAJOR, MY_MINOR), NULL, MY_NODE_NAME1); 
	device_create(my_class, NULL, MKDEV(MY_MAJOR, MY_MINOR+1), NULL, MY_NODE_NAME2); 
	printk("system auto make node : /dev/%s\n", MY_NODE_NAME1);
	printk("system auto make node : /dev/%s\n", MY_NODE_NAME2);





	// -- make 
	msg          = (char *)kmalloc(32, GFP_KERNEL);
	if (msg !=NULL)
		printk("malloc allocator address: 0x%p\n", msg);
	
	printk("***** LED GPIO Init ******************\n");
	if(gpio_is_valid(LED0) < 0){
		printk("gpio %d is valid error \n", LED0);
		return -1;
	}
	if(gpio_is_valid(LED1) < 0){
		printk("gpio %d is valid error \n", LED1);
		return -1;
	}
	if(gpio_request(LED0,"LED0_GPIO") < 0){
		printk("gpio %d is request error \n", LED0);
		return -1;
	}
	if(gpio_request(LED1,"LED1_GPIO") < 0){
		printk("gpio %d is request error \n", LED1);
		return -1;
	}
	if(gpio_request(COM,"COM_GPIO") < 0){
		printk("gpio %d is request error \n", LED1);
		return -1;
	}
	gpio_direction_output(LED0, 0);
	gpio_direction_output(LED1, 0);
	gpio_direction_output(COM, 1);
	
        return 0;
}



/*
 * CLEANUP_MODULE -- MODULE END --
 * */
void led_remove_module(void)
{
	dev_t devno;
        printk("<1> Goodbye\n");

	gpio_set_value(LED0,0);
	gpio_set_value(LED1,0);
	gpio_free(LED0);
	gpio_free(LED1);
	gpio_free(COM);
	devno = MKDEV(MY_MAJOR, MY_MINOR);

	if (msg){
        /* release the malloc */
        kfree(msg);
	}


	device_destroy(my_class,MKDEV(MY_MAJOR,MY_MINOR));
	device_destroy(my_class,MKDEV(MY_MAJOR,MY_MINOR +1 ));
	class_destroy(my_class);

	unregister_chrdev_region(devno, MY_DEV_COUNT);
	cdev_del(&my_cdev);
}


/*
 * file operation: OPEN 
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
 * file operation: READ
 * */
static ssize_t my_read(struct file *filp, char *buff, size_t len, loff_t *off)
{
	int major, minor;
	char led_value;
	short count;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,19,0)
	major = MAJOR(filp->f_inode->i_rdev);
	minor = MINOR(filp->f_inode->i_rdev);
#else
	major = MAJOR(filp->f_dentry->d_inode->i_rdev);
	minor = MINOR(filp->f_dentry->d_inode->i_rdev);
#endif

	switch(minor){
		case 0:
			led_value = gpio_get_value(LED0);
			msg[0] = led_value;
			len = 1;
			break;
		case 1:
			led_value = gpio_get_value(LED1);
			msg[0] = led_value;
			len = 1;
			break;
		default:
			led_value = -1;
			len = 0;
	}


	count = copy_to_user(buff, msg, len);
	printk("GPIO%d=%d, GPIO%d=%d\n",LED0 ,gpio_get_value(LED0),LED1,gpio_get_value(LED1));

	return 0;
}


/*
 * file operation: WRITE
 * */
static ssize_t my_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
	int major, minor;
	short count;

	// -- need to get the device minor number because we have two devices
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,19,0)
	major = MAJOR(filp->f_inode->i_rdev);
	minor = MINOR(filp->f_inode->i_rdev);
#else
	major = MAJOR(filp->f_dentry->d_inode->i_rdev);
	minor = MINOR(filp->f_dentry->d_inode->i_rdev);
#endif

	// -- copy the string from the user space program which open and write this device
	memset(msg, 0, 32);
	count = copy_from_user( msg, buff, len );

	if (msg[0]=='1') {
		if(minor == 0) gpio_set_value(LED0, 1);     // LED 0 ON
		if(minor == 1) gpio_set_value(LED1, 1);     // LED 1 ON
	} else if (msg[0]=='0') {
		if(minor == 0) gpio_set_value(LED0, 0);     // LED 0 OFF
		if(minor == 1) gpio_set_value(LED1, 0);     // LED 1 OFF
	}  else 
		printk("Unknown command , 1 or 0 \n");

printk("%s called \n",__func__);
	return len;
}



/*
 * file operation : CLOSE
 * */
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



module_init(led_init_module);
module_exit(led_remove_module);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ITtraining.com.tw");
MODULE_DESCRIPTION("A Simple GPIO Device Driver module for RaspPi");
