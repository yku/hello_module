#include <linux/kobject.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/sysfs.h>

static struct kobject *g_kobj;

static ssize_t
show_version(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "v0.1\n");
}
static DEVICE_ATTR(version, S_IRUGO, show_version, NULL);

static ssize_t
show_echo(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "Hello World\n");
}
static DEVICE_ATTR(echo, S_IRUGO, show_echo, NULL);

static struct attribute *hello_sysfs_attrs[] = {
    &dev_attr_version.attr,
    &dev_attr_echo.attr,
    NULL
};

static struct attribute_group hello_attr_group = {
    .name = "hello_child",
    .attrs = hello_sysfs_attrs,
};

const struct attribute_group *hello_attr_groups[] = {
    &hello_attr_group,
    NULL
};

static int __init
hello_init(void)
{
    int ret;
    
    printk("%s called!\n", __func__);

    g_kobj = kobject_create_and_add("hello_mod", kernel_kobj);
    if(!g_kobj)
        return -ENOMEM;
    ret = sysfs_create_groups(g_kobj, hello_attr_groups);
    if(ret)
        kobject_put(g_kobj);

    return ret;
}

static void __exit
hello_exit(void)
{
    printk("%s called!\n", __func__);
    if(g_kobj)
        kobject_put(g_kobj);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
