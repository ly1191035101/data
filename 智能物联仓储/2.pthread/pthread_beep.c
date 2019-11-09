#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "main.h"
void *pthread_beep(void *arg)
{
	char buf1[2] = {0};
	char beep[4] = "20";
	int fd;
	fd = open("/dev/beep_driver",O_RDWR);
	if(fd == -1){
		perror("open error\n");
	}
	while(1){
		if(buf[0] == '2'){
			if( beep[1] != buf[1]){
				beep[1] = buf[1];
				switch(beep[1]){
					case '0':
					buf1[0] = 0;
					write(fd,buf1,sizeof(buf1));
					break;
					case '1':
					buf1[0] = 1;
					write(fd,buf1,sizeof(buf1));
				}
			}


		}
		sleep(1);
	}
	close(fd);
}