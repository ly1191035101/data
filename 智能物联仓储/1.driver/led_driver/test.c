#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char buf[3] = {1,0,0};

int main(int argc, const char *argv[])
{
	int fd;
	
	fd = open("/dev/led_driver",O_RDWR);
	if(fd == -1){
		perror("open error");
		return -1;
	}
	
	while(1){
		write(fd,buf,sizeof(buf));
		sleep(1);
		buf[0] = buf[0]?0:1;
	}

	close(fd);

	return 0;
}
