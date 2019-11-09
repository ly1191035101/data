#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <linux/in.h>  //sockaddr_in
#include "main.h"
int main(int argc, const char *argv[])
{
	pthread_create(&tid[0],NULL,pthread_led,NULL);
	pthread_create(&tid[1],NULL,pthread_beep,NULL);
	pthread_create(&tid[2],NULL,pthread_data,NULL);
	pthread_create(&tid[3],NULL,pthread_led2,NULL);
	pthread_create(&tid[4],NULL,pthread_beep2,NULL);
	pthread_create(&tid[5],NULL,pthread_fan2,NULL);
	pthread_create(&tid[6],NULL,pthread_tube,NULL);
	pthread_create(&tid[7],NULL,pthread_transfer,NULL);
	pthread_create(&tid[8],NULL,pthread_transfer_data,NULL);
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
	{
		perror("socket failed.");
		exit(-1);
	}
	printf("socket ok.\n");
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;            //填充协议 IPv4
	serveraddr.sin_port = htons(8889);                 // 端口号 
	serveraddr.sin_addr.s_addr = inet_addr("192.168.8.4");  //IP
	socklen_t addrlen = sizeof(serveraddr);
	//2) bind(),绑定，把socket()函数返回的文件描述符和IP、端口号进行绑定;
	if(bind(sockfd,(struct sockaddr *)&serveraddr,addrlen) < 0)
	{
		perror("bind failed.");
		exit(-1);
	}
	printf("bind ok.\n");
	if(listen(sockfd,20) < 0)
	{
		perror("bind failed.");
		exit(-1);
	}
	printf("listen ok.\n");
	acceptfd = accept(sockfd,NULL,NULL);
	printf("acceptfd ok.\n");
	while(1)
	{
		recv(acceptfd,buf,sizeof(buf),0);
		if(buf[0] == '7'){
			memset(buf,0,sizeof(buf));
			recv(acceptfd,&variable,sizeof(variable),0);
//			printf("temp_max:%f max_ill:%f max_hum %f temp_min:%f ill_min:%f hum_min:%f\n",\
					variable.MAX_temperature,variable.MAX_ill,variable.MAX_humidity,\
					variable.MIN_temperature,variable.MIN_ill,variable.MIN_humidity);
		}
	}
	return 0;
}
