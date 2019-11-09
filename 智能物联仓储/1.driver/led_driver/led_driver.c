#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/device.h>
#define RED_BASE 0xC001A000
#define BLUE_BASE 0xC001B000
#define GREEN_BASE 0xC001E000


unsigned int *red_base = NULL;
unsigned int *blue_base = NULL;
unsigned int *green_base = NULL;

#define CNAME "led_driver"
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
		//灭灯
		*red_base &= ~(1<<28);
	}else{
		//亮灯
		*red_base |= (1<<28);
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

static int __init led_init(void)
{
	//注册字符设备驱动
	major = register_chrdev(major,CNAME,&fops);
	if(major < 0){
		printk("register char device error\n");
		return major;
	}

	//2.reb_led operations
	red_base = ioremap(RED_BASE,36);
	if(red_base == NULL){
		printk("red ioremap error\n");
		return -ENOMEM;
	}
	blue_base = ioremap(BLUE_BASE,36);
	if(blue_base == NULL){
		printk("blue ioremap error\n");
		return -ENOMEM;
	}
	green_base = ioremap(GREEN_BASE,36);
	if(green_base == NULL){
		printk("green ioremap error\n");
		return -ENOMEM;
	}

	*red_base &= ~(1<<28);
	*(red_base+1) |= (1<<28);
	*(red_base+9) &= ~(3<<24);

	*blue_base &= ~(1<<12);
	*(blue_base+1) |= (1<<12);
	*(blue_base+8) &= ~(3<<24);
	*(blue_base+8) |= (1<<25);

	*green_base &= ~(1<<13);
	*(green_base+1) |= (1<<13);
	*(green_base+8) &= ~(3<<26);
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

static void __exit led_exit(void)
{
	iounmap(green_base);
	iounmap(blue_base);
	iounmap(red_base);
	class_destroy(cls);
	device_destroy(cls,MKDEV(major,0));
	//注销字符设备驱动
	unregister_chrdev(major,CNAME);
}
module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");








