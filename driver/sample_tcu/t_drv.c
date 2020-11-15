/* GPIO Push Button driver by FANCONG */

#include <linux/kernel.h>
#include <linux/init.h>
#include <asm/bitops.h>

#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/clk.h>
#include <linux/pwm.h>
#include <linux/file.h>
#include <linux/list.h>
#include <linux/gpio.h>
#include <linux/time.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/kthread.h>
#include <linux/mfd/core.h>
#include <linux/mempolicy.h>
#include <linux/interrupt.h>
#include <linux/mfd/jz_tcu.h>
#include <linux/miscdevice.h>

#include <soc/irq.h>
#include <soc/base.h>
#include <soc/extal.h>

#include <asm/io.h>
#include <asm/irq.h>
#include <asm/uaccess.h>
#include <asm/cacheflush.h>
#include <soc/gpio.h>

#include "t_drv.h"

#define DRV_DBG

#ifdef DRV_DBG
#define DRV_LOG printk
#else
#define DRV_LOG(x...) ((void)0)
#endif

static int drv_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int drv_release(struct inode *inode, struct file *file)
{
    return 0;
}

static long drv_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int ret = 0;

    switch (cmd)
    {
    case CTRL_TEST:
    {
        //ret = copy_from_user(&group_bit_info, (gpio_groupbit_info *)arg, sizeof(gpio_groupbit_info));
        //if (ret)
        //{
        //    printk("copy_from_user fail \n");
        //    return -1;
        //}
        //ret = copy_to_user((void __user *)arg, &group_bit_info, sizeof(gpio_groupbit_info));
        //if (ret)
        //{
        //    printk("copy_to_user fail \n");
        //    return -1;
        //}
        DRV_LOG("[%s %d]\n", __func__, __LINE__);
        break;
    }

    default:
    {
        break;
    }
    }
    return ret;
}

static struct file_operations drv_fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = drv_ioctl,
    .open = drv_open,
    .release = drv_release,
};

static struct miscdevice drv_miscdev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "drv_ctrl",
    .fops = &drv_fops,
};

static int __init drv_init(void)
{
    int ret;

    ret = misc_register(&drv_miscdev);
    if (ret < 0)
    {
        printk(KERN_ERR "tlclk: misc_register returns %d.\n", ret);
        return ret;
    }

    return 0;
}

static void __exit drv_exit(void)
{
    misc_deregister(&drv_miscdev);
}

module_init(drv_init);
module_exit(drv_exit);

MODULE_LICENSE("GPL");
