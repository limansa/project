// Simple Character Device Driver Module for Raspberry Pi.

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
#include <mach/gpio.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/spi/spi.h>
#include <linux/io.h>


//
// 這裡使用arch/arm/mach-bcm2708/bcm2708.c 裡面已經準備好的platform_device for spi
//
#define MY_DEV_NAME "my_spi_master"



// ref to arch/arm/mach-bcm2708/include/platform.h
#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000)
//#define SPI0_BASE                (BCM2708_PERI_BASE + 0x204000)


/* *********************************************
 * PLATFORM DRIVER 
 * location : arch/driver/
 * *********************************************
 * */

// -- PROBE 
static int MY_SPI_MASTER_probe(struct platform_device *pdev)
{
	// get resource 
	struct resource *regs;
	u32 *gpio ;
	u32 *spi_base;
	u32 *spi_fifo ;
	int rx_len, tx_len;
	u32 msg[6];
	u32 cmd[6];
	int i ;
	i = 6;
	while(i--)msg[i] = 0;
	printk("my spi master probe\n");

	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!regs) {
		dev_err(&pdev->dev, "could not get IO memory\n");
		return -ENXIO;
	}

	// -- init_pinmode
	// GPIO07=CE1 ; GPIO08=CE0 ; GPIO09=MISO ; GPIO10=MOSI ; GPIO11=CLK
	gpio = ioremap(GPIO_BASE, SZ_16K);
	printk("gpio:%p\n", gpio);
	*gpio     &=~((1<<21) | (1<<22) | (1<<23));  // GPIO07 as input
	*gpio     &=~((1<<24) | (1<<25) | (1<<26));  // GPIO08 as input
	*gpio     &=~((1<<27) | (1<<28) | (1<<29));  // GPIO09 as input
	*(gpio+1) &=~((1<<0 ) | (1<<1 ) | (1<<2 ));  // GPIO10 as input
	*(gpio+1) &=~((1<<3 ) | (1<<4 ) | (1<<5 ));  // GPIO10 as input

	*gpio     |= (                    (1<<23));  // GPIO07 as alt0:SPI 
	*gpio     |= (                    (1<<26));  // GPIO08 as alt0:SPI
	*gpio     |= (                    (1<<29));  // GPIO09 as alt0:SPI
	*(gpio+1) |= (                    (1<<2 ));  // GPIO10 as alt0:SPI
	*(gpio+1) |= (                    (1<<5 ));  // GPIO10 as alt0:SPI
	iounmap(gpio);
	
	// -- initialise the spi master hardware 
	regs = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!regs) {
		dev_err(&pdev->dev, "could not get IO memory\n");
		return -ENXIO;
	}

	// get the spi base register 
	spi_base = ioremap(regs->start, resource_size(regs));
	if (!spi_base) {
		dev_err(&pdev->dev, "could not remap memory\n");
		return 0;
	}
	printk("regs->start=%p,spi_base:%p\n",regs->start, spi_base);

	*spi_base             = 0x00; 
	*spi_base            |= ((1<<4) | (1<<5)); // clear tx,rx fifo
	*spi_base            &=~((1<<2) | (1<<3)); // setup SPI mode 0 : CPOL and CPHA = 0
	*(spi_base + 0x08/4 ) = 0x00;  // setup CLK_DIV as 65535
	*(spi_base)          &=~((1<<0) | (1<<1));// chip select :CS0
	*(spi_base)          &=~( 1<<21) ; // CSPOL0


	// Try to Read the Company ID and Device ID from the spi0.0
	spi_fifo = spi_base + 0x0004/4;
	// clear tx,rx fifo 
	*spi_base            |= ((1<<4) | (1<<5)); // clear tx,rx fifo
	
	*spi_base            |= (1<<7); // set TA
	// transaction: 
	rx_len = 0;
	tx_len = 0;
	cmd[0] = 0x9f;
	cmd[1] = 0x0;
	cmd[2] = 0x0;
	cmd[3] = 0x0;
	cmd[4] = 0x0;
	cmd[5] = 0x0;
	while((rx_len < 6) || (tx_len < 6)){
		while((readl(spi_base) & (1<<18))&& (tx_len < 6) ){
			writel(cmd[tx_len],spi_fifo);
			tx_len ++;
		}

		while((readl(spi_base) & (1<<17))&& (rx_len < 6) ){
			msg[rx_len] = readl(spi_fifo);
			rx_len++;
		}
	}

	*spi_base            &=~(1<<7); // clear TA
	iounmap(spi_base);
	for(i=0 ;i<6 ;i++ ){
		printk("msg[%d]=%X\n", i,msg[i]);
	}
	return 0;
}

// -- REMOVE
static int MY_SPI_MASTER_remove(struct platform_device *pdev)
{
	return 0;
}


// -- PLATFORM DRIVER OBJECT
static struct platform_driver MY_SPI_MASTER_driver= {
	.driver		= {
		.name	= MY_DEV_NAME,
		.owner	= THIS_MODULE,
	},
	.probe		= MY_SPI_MASTER_probe,
	.remove		= MY_SPI_MASTER_remove,
};


// -- Module INIT
static int __init MY_SPI_MASTER_init(void)
{
	printk("my spi master init\n");
	//return platform_driver_probe(&MY_SPI_MASTER_driver, MY_SPI_MASTER_probe);
	return platform_driver_register(&MY_SPI_MASTER_driver);
}

static void __exit MY_SPI_MASTER_exit(void)
{
	printk("my spi master exit\n");
	platform_driver_unregister(&MY_SPI_MASTER_driver);
}

module_init(MY_SPI_MASTER_init);
module_exit(MY_SPI_MASTER_exit);

MODULE_DESCRIPTION("Platform device and driver example");
MODULE_AUTHOR("ITTraining");
MODULE_LICENSE("GPL v2");
//MODULE_ALIAS("platform:" MY_SPI_MASTER_PLATFORM_DEV_NAME);
