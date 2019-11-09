#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include "main.h"
//#include "data_global.h"
#define STORAGE_NO	2
#define STORAGE_NUM 		5
#define N 32
struct storage_goods_info
{
	unsigned char goods_type;
	unsigned int goods_count;
};
struct storage_info
{
	unsigned char storage_status;				// 0:open 1:close
	unsigned char led_status;
	unsigned char buzzer_status;
	unsigned char fan_status;
	unsigned char seg_status;
	signed char x;
	signed char y;
	signed char z;
	char samplingTime[20];
	float temperature;
	float temperatureMIN;
	float temperatureMAX;
	float humidity;
	float humidityMIN;
	float humidityMAX;
	float illumination;
	float illuminationMIN;
	float illuminationMAX;
	float battery;
	float adc;
	float adcMIN;
	struct storage_goods_info goods_info[10];
};

struct env_info_clien_addr
{
	struct storage_info storage_no[STORAGE_NUM];	
};
// 共享内存结构体
struct shm_addr
{
	char cgi_status;
	char qt_status;
	struct env_info_clien_addr rt_status;
};
struct _rt_info{
	unsigned char sto_status;				// 0:open 1:close
	unsigned char led_status;
	unsigned char beep_status;
	unsigned char fan_status;
	unsigned char seg_status;
	signed char x;
	signed char y;
	signed char z;
	float tem;
	float temMIN;
	float temMAX;
	float hum;
	float humMIN;
	float humMAX;
	float ill;
	float illMIN;
	float illMAX;
	float bat;
	float adc;
};
void P(int a,int b)
{
	struct sembuf sbuf;
	sbuf.sem_num = b;
	sbuf.sem_op = -1;
	sbuf.sem_flg = 0;
	semop(a,&sbuf,1);
}
void V(int a,int b)
{
	struct sembuf sbuf;
	sbuf.sem_num = b;
	sbuf.sem_op = +1;
	sbuf.sem_flg = 0;
	semop(a,&sbuf,1);
}
void *pthread_transfer_data(void *arg)
{
	key_t key;
	int semid;
	int shmid;
	struct shm_addr *shm_buf = NULL;
	if((key = ftok("/app", 'i')) < 0)
	{
		perror("ftok");
		exit(1);
	}

	if((semid  = semget(key, 1,IPC_CREAT | 0666)) < 0)//打开信号灯
	{
		perror("semget");
		exit(1);
	}

	if((shmid = shmget(key, N, IPC_CREAT | 0666 )) == -1)//共享内存的创建
	{
		perror("shmget");
		exit(1);
	}

	if((shm_buf = (struct shm_addr*)shmat(shmid, NULL, 0)) == (void*)-1)//共享内存的隐射
	{
		perror("shmat");
		exit(1);
	}
	while(1){

    shm_buf->rt_status.storage_no[STORAGE_NO].storage_status=1;
	shm_buf->rt_status.storage_no[STORAGE_NO].led_status=1;
	shm_buf->rt_status.storage_no[STORAGE_NO].buzzer_status=1;
	shm_buf->rt_status.storage_no[STORAGE_NO].fan_status=1;
	shm_buf->rt_status.storage_no[STORAGE_NO].seg_status=1;	
	shm_buf->rt_status.storage_no[STORAGE_NO].x=conver.x;
	shm_buf->rt_status.storage_no[STORAGE_NO].y=conver.y;
	shm_buf->rt_status.storage_no[STORAGE_NO].z=conver.z;
	shm_buf->rt_status.storage_no[STORAGE_NO].temperature=conver.temperature;
	shm_buf->rt_status.storage_no[STORAGE_NO].temperatureMIN=variable.MIN_temperature;
	shm_buf->rt_status.storage_no[STORAGE_NO].temperatureMAX=variable.MAX_temperature;
	shm_buf->rt_status.storage_no[STORAGE_NO].humidity=conver.humidity;
	shm_buf->rt_status.storage_no[STORAGE_NO].humidityMIN=variable.MIN_humidity;
	shm_buf->rt_status.storage_no[STORAGE_NO].humidityMAX=variable.MAX_humidity;
	shm_buf->rt_status.storage_no[STORAGE_NO].illumination=conver.ill;
	shm_buf->rt_status.storage_no[STORAGE_NO].illuminationMIN=variable.MIN_ill;
	shm_buf->rt_status.storage_no[STORAGE_NO].illuminationMAX=variable.MAX_ill;
	shm_buf->rt_status.storage_no[STORAGE_NO].battery=conver.bet;
	shm_buf->rt_status.storage_no[STORAGE_NO].adc=conver.adc;
	V(semid,0);
		sleep(1);
	}
	return 0;
}
