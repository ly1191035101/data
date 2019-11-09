#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/device.h>
#define BEEP_BASE 0xC001C000

unsigned int *beep_base = NULL;

#define CNAME "beep_driver"
int major = 0;
struct class*cls;
struct device *dev;
char kbuf[128] = {0};
int mycdev_open(struct inode *inode, struct file *file)
{
	printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
		return 0;
}
ssize_t mycdev_read(struct file *file, char __user *ubuf,
		size_t size, loff_t *offs)
{
	int ret;
	printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
		if(size > sizeof(kbuf)) size = sizeof(kbuf);

	ret = copy_to_user(ubuf,kbuf,size);
	if(ret){
		printk("copy data to user error\n");
		return -EINVAL;
	}

	return size;

}
ssize_t mycdev_write(struct file *file, const char __user *ubuf,
		size_t size, loff_t *offs)
{
	int ret;

//	printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
		if(size > sizeof(kbuf)) size = sizeof(kbuf);

	ret = copy_from_user(kbuf,ubuf,size);
	if(ret){
		printk("copy data from user error\n");
		return -EINVAL;
	}
	if(kbuf[0] == 0){
		*(beep_base+8) &= ~(1<<28);
	}else{
		
		*(beep_base+8) |= (1<<28);
	}


	return size;
}
int mycdev_close(struct inode *inode, struct file *file)
{
	printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
		return 0;
}

const struct file_operations fops = {
	.open    = mycdev_open,
	.read    = mycdev_read,
	.write   = mycdev_write,
	.release = mycdev_close,
};

static int __init beep_init(void)
{
	//注册字符设备驱动
	major = register_chrdev(major,CNAME,&fops);
	if(major < 0){
		printk("register char device error\n");
		return major;
	}

     beep_base = ioremap(BEEP_BASE,36);
	if(beep_base == NULL){
		printk("beep ioremap error\n");
		return -ENOMEM;
	}
	*beep_base |= (1<<14);
	*(beep_base+1) |= (1<<14);
	*(beep_base+8) &= ~(3<<28);

	//自动创建设备节点
	cls = class_create(THIS_MODULE,CNAME);
	if(IS_ERR(cls)){
		printk("class create error\n");
		return PTR_ERR(cls);
	}
	dev = device_create(cls,NULL,MKDEV(major,0),NULL
			,CNAME);
	if(IS_ERR(dev)){
		printk("device create error\n");
		return PTR_ERR(dev);
	}
	return 0;
}

static void __exit beep_exit(void)
{
	iounmap(beep_base);
	class_destroy(cls);
	device_destroy(cls,MKDEV(major,0));
	//注销字符设备驱动
	unregister_chrdev(major,CNAME);
}
module_init(beep_init);
module_exit(beep_exit);
MODULE_LICENSE("GPL");








