/* #include <linux/module.h> */
/* #include <linux/kernel.h> */
/*   */
/* int init_module(void) */
/* { */
/* 	printk(KERN_INFO "init_module() called\n"); */
/* 	return 0; */
/* } */
/*   */
/* void cleanup_module(void) */
/* { */
/* 	printk(KERN_INFO "cleanup_module() called\n"); */
/* } */

#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

static dev_t first; // Global variable for the first device number

static int __init hello_start(void)
{
	printk(KERN_INFO "Loading hello module...\n");
	if (alloc_chrdev_region(&first, 0, 3, "helius") < 0) {
		return -1;
	}
	printk(KERN_INFO "<Major, Minor>: <%d, %d>\n", MAJOR(first), MINOR(first));
	printk(KERN_INFO "Hello world\n");
	return 0;
}
static void __exit hello_end(void)
{
	unregister_chrdev_region(first, 3);
	printk(KERN_INFO "Goodbye Mr.\n");
}
module_init(hello_start);
module_exit(hello_end);
