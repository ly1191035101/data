#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include "main.h"
#define LEN (sizeof(msg_1)-sizeof(long))
int msgid;
struct msg{
	long type;
	long msgtype;
	unsigned char text[32];
};

void *pthread_transfer(void *arg ){
	key_t key;
	struct msg msg_1;
	int re;
	key = ftok("/app",'g');
	if(key==-1){
		perror("ftok");
		return;
	}
	
	msgid = msgget(key,IPC_CREAT|0666);
	if(msgid==-1){
		perror("msgget");
		return;
	}
	while(1){
		re = msgrcv(msgid,&msg_1,LEN,1L,MSG_NOERROR);//超过LEN长度截断
		if(re==-1){
			perror("msgrcv");
			return;
		}
	printf("type=%ld,msg.type=%ld,msg.text=%d\n",msg_1.type,msg_1.msgtype,msg_1.text[0]);
	switch(msg_1.text[0]){
		case 0x10:
		//A53led
		strcpy(buf,"10");
		break;
		case 0x11:
		strcpy(buf,"11");
		break;
		//A53蜂鸣器
		case 0x0:
		strcpy(buf,"20");
		break;
		case 0x1:
		strcpy(buf,"21");
		break;
		//M0 Led
		case 0x60:
		strcpy(buf,"30");
		break;
		case 0x61:
		strcpy(buf,"31");
		break;
	//	M0 beep
		case 0x50:
		strcpy(buf,"40");
		break;
		case 0x51:
		strcpy(buf,"41");
		break;
	//M0 风扇
		case 0x40:
		strcpy(buf,"50");
		break;
		case 0x41:
		strcpy(buf,"51");
		break;
		case 0x42:
		strcpy(buf,"52");
		break;
		case 0x43:
		strcpy(buf,"53");
		break;
//    M0 数码管
		case 0x7f:
		strcpy(buf,"6f");
		break;
		case 0x70:
		strcpy(buf,"60");
		break;
		case 0x71:
		strcpy(buf,"61");
		break;
		case 0x72:
		strcpy(buf,"62");
		break;
		case 0x73:
		strcpy(buf,"63");
		break;
		case 0x74:
		strcpy(buf,"64");
		break;
		case 0x75:
		strcpy(buf,"65");
		break;
		case 0x76:
		strcpy(buf,"66");
		break;
		case 0x77:
		strcpy(buf,"67");
		break;
		case 0x78:
		strcpy(buf,"68");
		break;
		case 0x79:
		strcpy(buf,"69");
		break;
	}
	sleep(1);
	}
	return 0;
}

