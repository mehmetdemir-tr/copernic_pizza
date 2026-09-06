// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/vmalloc.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mehmet Demir");
MODULE_DESCRIPTION("RAM-Drive Cache Module");
MODULE_VERSION("0.2");

#define DEVICE_NAME "copernic_pizza"
#define CACHE_SIZE (16 * 1024 * 1024)

static int major;
static char *ram_disk_buffer;
static struct class *copernic_class;
static struct device *copernic_device;

static ssize_t dev_read(struct file *filep, char __user *buffer, size_t len, loff_t *offset)
{
	if (*offset >= CACHE_SIZE)
		return 0;
	if (*offset + len > CACHE_SIZE)
		len = CACHE_SIZE - *offset;
	if (len == 0)
		return 0;
	if (copy_to_user(buffer, ram_disk_buffer + *offset, len))
		return -EFAULT;
	*offset += len;
	return len;
}

static ssize_t dev_write(struct file *filep, const char __user *buffer, size_t len, loff_t *offset)
{
	if (*offset >= CACHE_SIZE)
		return -ENOSPC;
	if (*offset + len > CACHE_SIZE)
		len = CACHE_SIZE - *offset;
	if (copy_from_user(ram_disk_buffer + *offset, buffer, len))
		return -EFAULT;
	*offset += len;
	return len;
}

static int dev_open(struct inode *inodep, struct file *filep)
{
	return 0;
}

static int dev_release(struct inode *inodep, struct file *filep)
{
	return 0;
}

static const struct file_operations fops = {
	.open = dev_open,
	.read = dev_read,
	.write = dev_write,
	.release = dev_release,
};

static int __init cache_init(void)
{
	pr_info("Module is up.\n");
	pr_info("Most Hot Pizza innn this galaxy, innn this galaxy!.\n");

	ram_disk_buffer = vmalloc(CACHE_SIZE);
	if (!ram_disk_buffer)
		return -ENOMEM;
	memset(ram_disk_buffer, 0, CACHE_SIZE);

	major = register_chrdev(0, DEVICE_NAME, &fops);
	if (major < 0) {
		vfree(ram_disk_buffer);
		return major;
	}

	copernic_class = class_create(DEVICE_NAME);
	if (IS_ERR(copernic_class)) {
		unregister_chrdev(major, DEVICE_NAME);
		vfree(ram_disk_buffer);
		return PTR_ERR(copernic_class);
	}

	copernic_device = device_create(copernic_class, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
	if (IS_ERR(copernic_device)) {
		class_destroy(copernic_class);
		unregister_chrdev(major, DEVICE_NAME);
		vfree(ram_disk_buffer);
		return PTR_ERR(copernic_device);
	}

	snprintf(ram_disk_buffer, 100, "*recep ivedik laugh*");
	pr_info("Success: Mounted 16 MB Space from RAM! Addr: %p\n", ram_disk_buffer);
	return 0;
}

static void __exit cache_exit(void)
{
	pr_info("Module: Module is down.\n");
	device_destroy(copernic_class, MKDEV(major, 0));
	class_destroy(copernic_class);
	unregister_chrdev(major, DEVICE_NAME);
	vfree(ram_disk_buffer);
}

module_init(cache_init);
module_exit(cache_exit);
