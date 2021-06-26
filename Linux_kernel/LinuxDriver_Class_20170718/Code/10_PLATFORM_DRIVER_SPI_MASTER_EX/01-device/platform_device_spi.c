/*
 * onionys@IT-Robotics-Lab, Feb 4, 2015
 *  blog:
 *  email: onionys@ittraining.com
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
#include <linux/platform_device.h>
#include <mach/platform.h>
#include <mach/gpio.h>
#include <linux/time.h>
#include <linux/delay.h>

#include <linux/dma-mapping.h>

#define DMA_MASK_BITS_COMMON 32
#define MY_DEV_NAME "my_spi_master"

/* Resource Definition */

static struct resource bcm2708_spi_resources[] = {
	{
		.start = SPI0_BASE,
		.end = SPI0_BASE + SZ_256 - 1,
		.flags = IORESOURCE_MEM,
	}, {
		.start = IRQ_SPI,
		.end = IRQ_SPI,
		.flags = IORESOURCE_IRQ,
	}
};


/* Platform device definition */

static u64 bcm2708_spi_dmamask = DMA_BIT_MASK(DMA_MASK_BITS_COMMON);
static struct platform_device bcm2708_spi_device = {
	.name = MY_DEV_NAME,
	.id = 0,
	.num_resources = ARRAY_SIZE(bcm2708_spi_resources),
	.resource = bcm2708_spi_resources,
	.dev = {
		.dma_mask = &bcm2708_spi_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(DMA_MASK_BITS_COMMON)},
};

/* Register platform device */


static int __init my_bcm2708_spi_init(void)
{
	return platform_device_register(&bcm2708_spi_device);
}

static void __exit my_bcm2708_spi_exit(void)
{
	platform_device_unregister(&bcm2708_spi_device);
}

module_init(my_bcm2708_spi_init);
module_exit(my_bcm2708_spi_exit);

MODULE_DESCRIPTION("Platform Device example");
MODULE_AUTHOR("ITTraining");
MODULE_LICENSE("GPL v2");
