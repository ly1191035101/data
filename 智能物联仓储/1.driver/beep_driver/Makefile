#KERNELDIR:= /lib/modules/$(shell uname -r)/build/
KERNELDIR:= /home/linux/kernel-3.4.39/
PWD:=$(shell pwd)
all:
	make -C $(KERNELDIR) M=$(PWD) modules
	arm-none-linux-gnueabi-gcc test.c -o test
	cp *.ko test ~/rootfs/
clean:
	make -C $(KERNELDIR) M=$(PWD) clean

obj-m:=beep_driver.o
