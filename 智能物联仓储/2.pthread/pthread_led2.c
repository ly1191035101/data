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
void led_control1(int on,int fd_uart)
{
    uint8_t cmd;

    if(on){
        cmd = LED_ON;
    }else{
        cmd = LED_OFF;
    }
    write(fd_uart, &cmd, 1);
}
void *pthread_led2(void *arg)
{	
	char led2[4] = "30";
	int fd_uart = open(DEV_UART,O_RDWR);
	if(fd_uart == -1){
		perror("open error\n");
	}	 
	serial_init(fd_uart);
	while(1){
			if(buf[0] == '3'){
				if(led2[1] != buf[1]){
					led2[1] = buf[1];
					switch(led2[1]){
						case '0':
							led_control1(0,fd_uart);
						break;
						case '1':
							led_control1(1,fd_uart);
						break;
					}
				}
			}
		sleep(1);
	}
	close(fd_uart);
}