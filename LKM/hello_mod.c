/** System Programming : Hello Kernel Module v3 **/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Koung Chan Cho");
MODULE_DESCRIPTION("ERICA System Programming : Hello Module");

static int __init hello_init(void)
{
	printk(KERN_INFO "HELLO MODULE v3 is loaded... \n"); // kern_level.h
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "HELLO MODULE is unloaded... \n");
}

module_init(hello_init);
module_exit(hello_exit);
