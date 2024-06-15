#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/random.h>
#include <linux/slab.h>

#define DEVICE_NAME "gore"
#define CLASS_NAME "gore_class"

static char *malware[] = {
    "дайте гойду\n",
    "sog is nigger\n",
    "sog sex simulator dolod\n"
};

static int gore_open(struct inode *inode, struct file *file);
static int gore_release(struct inode *inode, struct file *file);
static ssize_t gore_read(struct file *file, char __user *buf, size_t count, loff_t *ppos);

static const struct file_operations gore_fops = {
    .owner      = THIS_MODULE,
    .open       = gore_open,
    .release    = gore_release,
    .read       = gore_read,
};

static int gore_major;
static struct class *gore_class;
static struct cdev gore_cdev;

static int __init gore_init(void)
{
    int ret;

    ret = alloc_chrdev_region(&gore_major, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        pr_err("%s: failed to register device: %d\n", DEVICE_NAME, ret);
        return ret;
    }

    cdev_init(&gore_cdev, &gore_fops);
    ret = cdev_add(&gore_cdev, gore_major, 1);
    if (ret < 0) {
        pr_err("%s: failed to add cdev: %d\n", DEVICE_NAME, ret);
        goto unregister_region;
    }

    gore_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(gore_class)) {
        pr_err("%s: failed to create class: %ld\n", DEVICE_NAME, PTR_ERR(gore_class));
        ret = PTR_ERR(gore_class);
        goto remove_cdev;
    }

    device_create(gore_class, NULL, gore_major, NULL, DEVICE_NAME);

    pr_info("%s: driver successfully loaded\n", DEVICE_NAME);
    return 0;

remove_cdev:
    cdev_del(&gore_cdev);
unregister_region:
    unregister_chrdev_region(gore_major, 1);
    return ret;
}

static void __exit gore_exit(void)
{
    device_destroy(gore_class, gore_major);
    class_destroy(gore_class);
    cdev_del(&gore_cdev);
    unregister_chrdev_region(gore_major, 1);
    pr_info("%s: successfully liquidated\n", DEVICE_NAME);
}

static int gore_open(struct inode *inode, struct file *file)
{
    pr_info("%s: opened\n", DEVICE_NAME);
    return 0;
}

static int gore_release(struct inode *inode, struct file *file)
{
    pr_info("%s: closed\n", DEVICE_NAME);
    return 0;
}

static ssize_t gore_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    int message_idx = prandom_u32_max(ARRAY_SIZE(malware));
    size_t message_len = strlen(malware[message_idx]);
    ssize_t ret;

    if (*ppos >= message_len)
        return 0;

    if (count > message_len - *ppos)
        count = message_len - *ppos;

    ret = copy_to_user(buf, malware[message_idx] + *ppos, count);
    if (ret)
        return -EFAULT;

    *ppos += count;
    return count;
}

module_init(gore_init);
module_exit(gore_exit);

MODULE_AUTHOR("nedokaka");
MODULE_DESCRIPTION("gore device¿");
MODULE_LICENSE("GPL");