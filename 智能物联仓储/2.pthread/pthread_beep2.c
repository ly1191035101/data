#include "main.h"
enum MO_CMD{
    FAN_OFF = STORE2|FAN|0x00,
    FAN_1 = STORE2|FAN|0x01,
    FAN_2 = STORE2|FAN|0x02,
    FAN_3 = STORE2|FAN|0x03,

    BEEP_OFF = STORE2|BEEP|0x00,
    BEEP_ON = STORE2|BEEP|0x01,
    BEEP_ALRRM_OFF = STORE2|BEEP|0x02,
    BEEP_ALRRM_ON = STORE2|BEEP|0x03,

    LED_OFF = STORE2|LED|0x00,
    LED_ON = STORE2|LED|0x01,
};
void beep_control1(int on,int fd_uart)
{
    uint8_t cmd;

    if(on){
        cmd = BEEP_ON;
    }else{
        cmd = BEEP_OFF;
    }
    write(fd_uart, &cmd, 1);
}
void *pthread_beep2(void *arg)
{	
	char beep2[4] = "40";
	int fd_uart = open(DEV_UART,O_RDWR);
	if(fd_uart == -1){
		perror("open error\n");
	}	 
	serial_init(fd_uart);
	while(1){
		if (buf[0] == '4'){
			
		if (beep2[1] != buf[1]){
			beep2[1] = buf[1];
			switch(beep2[1]){
				case '0':
				beep_control1(0,fd_uart);
					break;
				case '1':
				beep_control1(1,fd_uart);
					break;
			}		
		}
	}
		sleep(1);
	}
	close(fd_uart);
}