#ifndef __MAIN_H__
#define __MAIN_H__
#include <pthread.h>
#include <string.h>
//获取M0数据及数据转化
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define DEV_UART 			"/dev/ttyUSB0"
//仓库编号
#define STORE1  0x40
#define STORE2  0x80
#define STORE3  0xc0

//设备编号
#define FAN  0x00
#define BEEP 0x10
#define LED  0x20
#define TUBE 0x30
int sockfd,acceptfd;
pthread_t tid[10];
void *pthread_led(void *);
void *pthread_beep(void *);
void *pthread_data(void *);
void *pthread_led2(void *);
void *pthread_beep2(void *);
void *pthread_fan2(void *);
void *pthread_tube(void *);
void *pthread_transfer(void *);
void *pthread_transfer_data(void *);
char buf[4];
//数据转换后的环境信息
struct conver_env_info {
    int snum;		 //仓库编号
    float temperature;	 //温度	
    float humidity;		 //湿度
    float ill;		 //光照
    float bet;		 //电池电量
    float adc; 		 //电位器信息
    signed char x;			 //三轴信息
    signed char y;			 
    signed char z;			 
}conver;
//设置环境变量
struct environment_variable{
    float MAX_temperature;
    float MAX_ill;
    float MAX_humidity;
    float MIN_temperature;
    float MIN_ill;
    float MIN_humidity;

}variable;
#endif
