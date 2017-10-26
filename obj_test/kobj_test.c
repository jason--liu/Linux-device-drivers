#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/kernel.h>

static ssize_t	my_sysfs_show (struct kobject *kobj, struct attribute *attr, char *buf)
{
    printk("my_sysfs_show\n");
    printk("attrname:%s\n", attr->name);

    sprintf(buf, "%s\n", attr->name);
    return strlen(attr->name) + 1;
}

static ssize_t my_sysfs_store (struct kobject *kojb, struct attribute *attr, const char *buf, size_t count)
{
    printk("my_sysfs_store\n");
    printk("write:%s\n", buf);

    return count;
}

struct attribute my_attrs = {
    .name = "lqy_kobj",
    .mode = S_IRWXUGO,
};

struct attribute *my_attrs_def[] = {
    &my_attrs,
    NULL,
};

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
    .default_attrs = my_attrs_def,
};
struct kobject my_kobj;

static int kobj_test_init(void)
{
    int err;
    printk("kobj_test init");
    err = kobject_init_and_add(&my_kobj, &my_ktype, NULL, "lqy");
    if (err < 0) {
        printk(KERN_ERR "kobject_init_and_add failed: %d\n", err);
        return err;
    }

    return 0;
}

static void kobj_test_exit(void)
{
    printk("kobj_test exit\n");
    kobject_del(&my_kobj);
}

module_init(kobj_test_init);
module_exit(kobj_test_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jason-Liu");