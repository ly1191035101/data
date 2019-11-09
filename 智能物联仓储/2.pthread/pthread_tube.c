#include "main.h"
enum MO_CMD{
	TUBE_OFF = STORE2|TUBE|0x0f,
	TUBE_0 =STORE2|TUBE|0x00,
	TUBE_1 =STORE2|TUBE|0x01,
	TUBE_2 =STORE2|TUBE|0x02,
	TUBE_3 =STORE2|TUBE|0x03,
	TUBE_4 =STORE2|TUBE|0x04,
	TUBE_5 =STORE2|TUBE|0x05,
    TUBE_6 =STORE2|TUBE|0x06,
	TUBE_7 =STORE2|TUBE|0x07,
	TUBE_8 =STORE2|TUBE|0x08,	
	TUBE_9 =STORE2|TUBE|0x09,	
};
void tube_control(char on,int fd_uart)
{
    uint8_t cmd;
	switch(on){
		case 'f':
		cmd = TUBE_OFF;
		break;
		case '0':
		cmd = TUBE_0;
		break;		
		case '1':
		cmd = TUBE_1;
		break;
		case '2':
		cmd = TUBE_2;
		break;
		case '3':
		cmd = TUBE_3;
		break;
		case '4':
		cmd = TUBE_4;
		break;
		case '5':
		cmd = TUBE_5;
		break;
		case '6':
		cmd = TUBE_6;
		break;
		case '7':
		cmd = TUBE_7;
		break;
		case '8':
		cmd = TUBE_8;
		break;
		case '9':
		cmd = TUBE_9;		
		break;
	}
    write(fd_uart, &cmd, 1);
}
void *pthread_tube(void *arg)
{
	char tube[4] = "6f";
	int fd;
	int fd_uart = open(DEV_UART,O_RDWR);
	if(fd_uart == -1){
		perror("open error\n");
	}	 
	serial_init(fd_uart);
	while(1){
		if(buf[0] == '6'){
			if(tube[1]!=buf[1]){
				tube[1] = buf[1];
				tube_control(tube[1],fd_uart);
			}
			
		}
		sleep(1);
	}
}