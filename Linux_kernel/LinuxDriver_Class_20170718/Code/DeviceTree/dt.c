#include <linux/init.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/kernel.h>

#define DRV_NAME      "eeprom_i2c"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ittraining");
 
static int test_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
  
  
   const char* cp;
   int cplen;
    const __be32 *val;
   struct device_node *matched_node=client->dev.of_node;
    pr_info("i2c probing\n");
        cp = of_get_property(matched_node, "compatible", &cplen);
        if (cp == NULL) {
			 pr_info("No compatible property\n");
		} else if (cplen > 0) {
			pr_info("%s %d\n",cp,cplen); 
		   // if (!strcmp(status, "okay") 
        }
 
     val = of_get_property(matched_node, "reg", NULL);
     if (val) pr_info("reg=<%#x>\n",be32_to_cpup(val)); 
     val = of_get_property(matched_node, "page_size", NULL);
     if (val) pr_info("page_size=<%d>\n",be32_to_cpup(val)); 
     val = of_get_property(matched_node, "byte_len", NULL);
     if (val) pr_info("byte_len=<%d>\n",be32_to_cpup(val)); 	 
   return 0;
}

static int test_i2c_remove(struct i2c_client *pclient)
{
   pr_info("i2c removing\n");
   return 0;
}

//joseph: should match dts compatible string exactly, "i.e. strcmp()"
static const struct of_device_id eeprom_of_match[] = {
     { .compatible = "atmel,24c64" },
     { .compatible = "atmel,at24c02"},
 //  { .compatible = "at24"},
   {},
};
MODULE_DEVICE_TABLE(of, eeprom_of_match);

static struct i2c_driver eeprom_i2c_driver = {
   .driver      = {
      .name   = DRV_NAME,
      .owner   = THIS_MODULE,
      .of_match_table = eeprom_of_match,
   },
   .probe      = test_i2c_probe,
   .remove      = test_i2c_remove,
};

static int __init eeprom_i2c_init(void)
{

    printk(KERN_INFO "i2c eeprom_i2c_init\n");
   return i2c_add_driver(&eeprom_i2c_driver);
}

static void __exit eeprom_i2c_exit(void)
{
   i2c_del_driver(&eeprom_i2c_driver);
}

module_init(eeprom_i2c_init);
module_exit(eeprom_i2c_exit);
