all:
	arm-linux-gcc main.c  pthread_transfer_data.c pthread_transfer.c pthread_tube.c pthread_led.c pthread_data.c pthread_beep.c pthread_led2.c pthread_fan2.c pthread_beep2.c -lpthread
	cp a.out ~/rootfs/
clean:
	rm *.out
