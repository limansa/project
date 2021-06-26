#include <linux/module.h>   
#include <linux/init.h>
#include <linux/fs.h>      
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/gpio.h>
#include <linux/version.h>
#include <asm/uaccess.h>

#define BUZZER 12 
#define LED1_GPIO 27 

#define MY_MAJOR  200
#define MY_MINOR  0
#define MY_DEV_COUNT 2

#define GPIO_ANY_GPIO_DEVICE_DESC    "myLED"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ITtraining.com.tw");
MODULE_DESCRIPTION("A Simple GPIO Device Driver module for RaspPi");

static int     my_open( struct inode *, struct file * );
static ssize_t my_read( struct file * ,        char *  , size_t, loff_t *);
static ssize_t my_write(struct file * , const  char *  , size_t, loff_t *);
static int     my_close(struct inode *, struct file * );

struct file_operations my_fops = {
    read    : my_read,
    write   : my_write,
    open    : my_open,
    release : my_close,
    owner   : THIS_MODULE
};

#define MSG_SIZE 32
static char *msg = NULL;
struct cdev  my_cdev;


//-- INIT_MODULE -- MODULE START--
int init_module(void)
{

    dev_t devno;
    unsigned int count = MY_DEV_COUNT; 
    int err;

    devno = MKDEV(MY_MAJOR, MY_MINOR);
    register_chrdev_region(devno, count , "myLED");

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
    printk("module gpio : Hello World. This is myLED Driver.\n");
    printk("'mknod /dev/buzzer c %d 0'.\n", MY_MAJOR);
    printk("'mknod /dev/myLED1 c %d 1'.\n", MY_MAJOR);

    // -- GPIO initial LED0
    err = gpio_is_valid(BUZZER);
    printk("gpio_is_valid: %d\n", err);
    if(err < 0){
        printk("gpio is valid error\n");
        return -1;
    }
    err = gpio_request(BUZZER, "BUZZER");
	printk("gpio_request return: %d\n", err);
    if(err < 0){
        printk("gpio request error\n");
        return -1;
    }
    gpio_direction_output(BUZZER, 0);

    // -- GPIO initial LED1
    err = gpio_is_valid(LED1_GPIO);
    printk("gpio_is_valid: %d\n", err);
    if(err < 0){
        printk("gpio is valid error\n");
        return -1;
    }
    err = gpio_request(LED1_GPIO, "LED1_GPIO");
	printk("gpio_request return: %d\n", err);
    if(err < 0){
        printk("gpio request error\n");
        return -1;
    }
    gpio_direction_output(LED1_GPIO, 0);

    // -- message buffer kmalloc
    printk("module gpio : msg malloc\n");
    msg          = (char *)kmalloc(MSG_SIZE, GFP_KERNEL);
    if (msg !=NULL)
        printk("malloc allocator address: 0x%p\n", msg);
    
    printk("module gpio : LED GPIO Init\n");
    return 0;
}


//-- CLEANUP_MODULE -- MODULE END --
void cleanup_module(void)
{
    dev_t devno;
    printk("module gpio: cleanup_moudle() \n");

    devno = MKDEV(MY_MAJOR, MY_MINOR);

    /* if the timer was mapped (final step of successful module init) */
    if (1){
        /* release the mapping */
        printk("module gpio: release gpio.addr\n");
        gpio_set_value(BUZZER,0);
        gpio_set_value(LED1_GPIO,0);
        gpio_free(BUZZER);
        gpio_free(LED1_GPIO);
    }
    if (msg){
        /* release the malloc */
        printk("module gpio: release msg\n");
        kfree(msg);
    }
    printk("module gpio: unregister chardev\n");
    unregister_chrdev_region(devno, MY_DEV_COUNT);
    cdev_del(&my_cdev);
}


// -- FILE OPERATION: OPEN --
static int my_open(struct inode *inod, struct file *fil)
{
    int major;
    int minor;
    major = imajor(inod);
    minor = iminor(inod);
    printk("module gpio: FILE OPEN MAJOR: %d MINOR: %d \n",major, minor);
    return 0;
}


// -- FILE OPERATION: READ --
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
            led_value = gpio_get_value(BUZZER);
            msg[0] = led_value;
            len = 1;
            break;
        case 1:
            led_value = gpio_get_value(LED1_GPIO);
            msg[0] = led_value;
            len = 1;
            break;
        default:
            led_value = -1;
            len = 0;
    }
    count = copy_to_user(buff, msg, len);
	printk("%d %d\n",gpio_get_value(BUZZER),gpio_get_value(LED1_GPIO));
    return 0;
}


// -- FILE OPERATION: WRITE --
static ssize_t my_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
    int major, minor;
    short count;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,19,0)
	major = MAJOR(filp->f_inode->i_rdev);
	minor = MINOR(filp->f_inode->i_rdev);
#else
	major = MAJOR(filp->f_dentry->d_inode->i_rdev);
	minor = MINOR(filp->f_dentry->d_inode->i_rdev);
#endif

    memset(msg, 0, MSG_SIZE);
    count = copy_from_user( msg, buff, len );

    switch(minor){
        case 0:
            if(msg[0] == '0')         
		    	 gpio_direction_input(BUZZER);  // buzzer off
            else if (msg[0] == '1') {  //// buzzer on
				gpio_direction_output(BUZZER, 0);
                gpio_set_value(BUZZER, 0);
			}
            break;
        case 1:
            if(msg[0] == '1') 
                gpio_set_value(LED1_GPIO, 1);
            else if (msg[0] == '0') 
                gpio_set_value(LED1_GPIO, 0);
            break;
        default:
            break;
    }
    return len;
}


// -- FILE OPERATION: CLOSE --
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
    printk("module gpio: CLOSE MAJOR %d MINOR %d\n",major, minor);
    return 0;
}

