#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "main.h"
void *pthread_led(void *arg)
{
	char buf1[3] = {0,0,0};
	char led[4] = "10";
	int fd;
	fd = open("/dev/led_driver",O_RDWR);
	if(fd == -1){
		perror("open error\n");
	}
	while(1){
		if(buf[0] == '1'){
			if(led[1] != buf[1]){
				led[1] = buf[1];
				switch(led[1]){
				case '0':
				buf1[0] = 0;
				write(fd,buf1,sizeof(buf1));
				break;
				case '1':
				buf1[0] = 1;
				write(fd,buf1,sizeof(buf1));
				break;
				}
			}
		}
		
		sleep(1);

	}
	close(fd);
}
