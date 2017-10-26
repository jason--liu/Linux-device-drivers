#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/kernel.h>

static ssize_t	my_sysfs_show (struct kobject *kobj, struct attribute *attr, char *buf)
{
    printk("my_sysfs_show\n");
    printk("attrname:%s", attr->name);

    sprintf(buf, "%s", attr->name);
    return strlen(attr->name) + 1;
}

static ssize_t my_sysfs_store (struct kobject *kojb, struct attribute *attr, const char *buf, size_t count)
{
    printk("my_sysfs_store\n");
    printk("write:%s\n", buf);

    return count;
}

static struct sysfs_ops my_sysfs_ops = {
    .show = my_sysfs_show,
    .store = my_sysfs_store,
};

static void my_obj_release (struct kobject *kobj)
{
    printk("release ok!\n");
}

static struct kobj_type my_ktype = {
    .release = my_obj_release,
    .sysfs_ops = &my_sysfs_ops,
};
struct kobject my_kobj;

static int kobj_test_init(void)
{
    printk("kobj_test init");
    kobject_init_and_add(&my_kobj, &my_ktype, NULL, "lqy");
}

static void kobj_test_exit(void)
{
    printk("kobj_test_exit\n");
    kobject_del(&my_kobj);
}

module_init(kobj_test_init);
module_exit(kobj_test_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jason-Liu");