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
struct env_info
{
	uint8_t head[3];	 //标识位st
	uint8_t type;		 //数据类型
	uint8_t snum;		 //仓库编号
	uint8_t temp[2];	 //温度	
	uint8_t hum[2];		 //湿度
	uint8_t x;			 //三轴信息
    uint8_t y;
    uint8_t z;
	uint32_t ill;		 //光照
	uint32_t bet;		 //电池电量
	uint32_t adc; 		 //电位器信息
};

static float dota_atof (char unitl)
{
    if (unitl > 100)
    {
        return unitl / 1000.0;
    }
    else if (unitl > 10)
    {
        return unitl / 100.0;
    }
    else
    {
        return unitl / 10.0;
    }
}

static int dota_atoi (const char *cDecade)
{
    int result = 0;
    if (' ' != cDecade[0])
    {
        result = (cDecade[0] - 48) * 10;
    }
    result += cDecade[1] - 48;
    return result;
}

static float dota_adc (unsigned int ratio)
{
    return ((ratio * 3.3) / 1024);
}
static float dota_bat (unsigned int ratio)
{
    return ((ratio * 3.34) / 1024);
}
void serial_init(int fd)
{
    struct termios options;
    tcgetattr(fd, &options);
    options.c_cflag |= ( CLOCAL | CREAD );
    options.c_cflag &= ~CSIZE;
    options.c_cflag &= ~CRTSCTS;
    options.c_cflag |= CS8;
    options.c_cflag &= ~CSTOPB;
    options.c_iflag |= IGNPAR;
    options.c_iflag &= ~(ICRNL | IXON);
    options.c_oflag = 0;
    options.c_lflag = 0;
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);
    tcsetattr(fd,TCSANOW,&options);
}

void *pthread_data(void *arg)
{
	int fd;
	//打开驱动文件
	fd = open(DEV_UART,O_RDWR);
	serial_init(fd);
	//设置初始环境变量
	struct env_info env;
	variable.MAX_temperature = 30;
    variable.MAX_ill = 150;
    variable.MAX_humidity = 30;
    variable.MIN_temperature = 0;
    variable.MIN_ill = 0;
    variable.MIN_humidity = 0;
	//关闭所有功能
	
	while(1){
	//进行数据转换		
	read(fd,&env,sizeof(env));
    conver.snum =env.snum;	 //仓库编号
    conver.temperature=env.temp[0] + dota_atof(env.temp[1]); //温度	
    conver.humidity= env.hum[0] + dota_atof(env.hum[1]);		 //湿度
    conver.ill= env.ill;		 //光照
    conver.bet= dota_bat(env.bet);		 //电池电量
    conver.adc= dota_adc(env.adc);		 //电位器信息   
    conver.x = env.x;			 //三轴信息
    conver.y = env.y;			 
    conver.z = env.z;	
	//根据环境自动报警
	if(conver.temperature > variable.MAX_temperature || conver.temperature < variable.MIN_temperature){
		strcpy(buf,"41");
	}else if(conver.ill > variable.MAX_ill || conver.ill < variable.MIN_ill){
		strcpy(buf,"41");
	}else if(conver.humidity > variable.MAX_humidity || conver.humidity < variable.MIN_humidity){
		strcpy(buf,"41");
	}
	send(acceptfd,&conver,sizeof(conver),0);	
//	printf("仓库:%d 温度:%f 湿度:%f 光照:%f 电量:%f 电位器:%f\n", conver.snum,conver.temperature,\
			conver.humidity,conver.ill, conver.bet,conver.adc);
//	printf("x:%d y:%d z:%d\n",conver.x,conver.y,conver.z);

	sleep(1);
	}
	close(fd);
	return 0;
}
