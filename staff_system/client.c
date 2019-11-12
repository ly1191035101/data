#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <linux/in.h>
#include <string.h>

#define N 128
void Administrator_login(int sockfd);
void user_login(int sockfd);
void admin_succeed(int sockfd);
void user_succeed(int sockfd,char *username);
void admin_query(int sockfd);
void admin_amend(int sockfd);
void admin_add(int sockfd);
void admin_del(int sockfd);
void admin_history(int sockfd);
void name_find(int sockfd);
void all_find(int sockfd);
void user_aiter(int sockfd);
//员工信息
struct user_msg{
	char staffno[N];
	char usertype[N];
	char name[N];
	char passwd[N];
	char age[N];
	char phone[N];
	char addr[N];
	char work[N];
	char date[N];
	char level[N];
	char salary[N];
}msg;
//历史记录
struct user_history{
	char date[N];
	char name[N];
	char words[N];
}msg_history;
int main(int argc, const char *argv[])
{
	//判断 是否输入 ip地址 和端口号
	if(argc < 3){
		printf("please user %s and ip and port\n",argv[0]);
		exit(-1);
	}
	int sockfd;
	//创建套接字，用于连接和通信
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0){
		perror("socket failed.");
		exit(-1);
	}
	//填充结构体sockaddr_in
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET; //填充协议 ipv4
	serveraddr.sin_port = htons(atoi(argv[2])); //填充端口号
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);//填充IP地址
	socklen_t addrlen = sizeof(serveraddr);
	//connect 连接
	if(connect(sockfd,(struct sockaddr *)&serveraddr,addrlen) < 0){
		perror("connect failed\n");
		exit(-1);
	}
	while(1){
		int num;
		printf("********************************\n");
		printf("***1.管理员 2.普通用户 3.退出***\n");
		printf("********************************\n");
		printf("请输入你的选择[数字]>>");
		scanf("%d",&num);
		switch (num){
		case 1:
			//管理员登录界面函数
			Administrator_login(sockfd);
			break;
		case 2:
			//用户登录界面函数
			user_login(sockfd);
			break;
		case 3:
			exit(1);
			break;
		default:
			printf("输入错误,请重新输入\n");
		}

	}
	return 0;
}
//管理员方式登录
void Administrator_login(int sockfd)
{
	char buf[N] = {0};
	char usertype[N] = "0";
	send(sockfd,usertype,sizeof(usertype),0);
	printf("------admin_or_user_login-------\n");
	printf("请输入用户名:");
	scanf("%s",buf);
	send(sockfd,buf,sizeof(buf),0);
	printf("请输入密码:");
	scanf("%s",buf);
	send(sockfd,buf,sizeof(buf),0);
	recv(sockfd,buf,sizeof(buf),0);
	printf("%s\n",buf);	
	if(buf[0] = 'a'){
		//管理员登录界面函数
		admin_succeed(sockfd);
	}
}
//用户登录
void user_login(int sockfd)
{
	char buf[N] = {0};
	char username[N] = {0};
	char usertype[N] = "1";
	send(sockfd,usertype,sizeof(usertype),0);
	printf("------admin_or_user_login-------\n");
	printf("请输入用户名:");
	scanf("%s",username);
	send(sockfd,username,sizeof(username),0);
	printf("请输入密码:");
	scanf("%s",buf);
	send(sockfd,buf,sizeof(buf),0);
	recv(sockfd,buf,sizeof(buf),0);
	printf("%s\n",buf);
	if(buf[0] == 'u'){
		//用户登录界面函数
		user_succeed(sockfd,username);
	}
}
//管理员登录界面函数
void admin_succeed(int sockfd)
{
	int i = 0;
	while(i!=6)
	{
		printf("***********************************\n");
		printf("* 1.查询用户 2.修改用户 3.添加用户*\n");
		printf("* 4.删除用户 5.查询历史 6.退出登录*\n");
		printf("***********************************\n");
		printf("请选择你要进行的操作(数字)>>");
		scanf("%d",&i);
		switch(i){
		case 1:
			//查询用户函数
			admin_query(sockfd);
			break;
		case 2:
			//修改用户函数
			admin_amend(sockfd);
			break;
		case 3:
			//添加用户函数
			admin_add(sockfd);
			break;
		case 4:
			//删除用户函数
			admin_del(sockfd);
			break;
		case 5:
			//查询历史函数
			admin_history(sockfd);
			break;
		case 6:
			send(sockfd,"7",sizeof("7"),0);
			break;
		default:
			printf("输入错误请重新输入:");
		}
	}
}
//查询用户函数
void admin_query(int sockfd)
{
	int i = 0;
	while(i != 3){
		printf("***********************************\n");
		printf("* 1.按人名查找 2.查找所有 3.退出  *\n");
		printf("***********************************\n");
		printf("请输入你的选择(数字)>>");
		scanf("%d",&i);
		switch(i){
		case 1:
			//按照姓名查找函数
			name_find(sockfd);
			break;
		case 2:
			//查找所有用户函数
			all_find(sockfd);
			break;
		case 3:
			break;
		default:
			printf("输入错误请重新输入:");
		}
	}
}
//按照姓名查找函数
void name_find(int sockfd)
{
	char buf[N] = {0};
	strcpy(buf,"1.name_find:");
	send(sockfd,buf,sizeof(buf),0);
	printf("请输入你要查找的姓名:");
	scanf("%s",buf);
	send(sockfd,buf,sizeof(buf),0);
	recv(sockfd,&msg,sizeof(msg),0);
	//判断用户名是否存在
	if(msg.staffno[0]!= 'n' ){
		printf("--------------------------------------------------------------\n");
		printf("工号 用户类型 姓名 密码 年龄 电话 地址 职位 入职年月 等级 工资\n");
		printf("%s %s %s %s %s %s %s %s %s %s %s\n",msg.staffno,msg.usertype,msg.name,\
				msg.passwd,msg.age,msg.phone,msg.addr,msg.work,msg.date,msg.level,msg.salary);
		printf("--------------------------------------------------------------\n");
	}else{
		memset(&msg,0,sizeof(msg));
		printf("用户名不存在\n");
		printf("%s",msg.staffno);
	}
}
//查找所有用户函数
void all_find(int sockfd)
{
	char buf[N] = {0};
	strcpy(buf,"2.all_find:");
	send(sockfd,buf,sizeof(buf),0);
	while(1){
		recv(sockfd,&msg,sizeof(msg),0);
		if(msg.salary[0] == 'q')
			break;
		printf("--------------------------------------------------------------\n");
		printf("工号 用户类型 姓名 密码 年龄 电话 地址 职位 入职年月 等级 工资\n");
		printf("%s %s %s %s %s %s %s %s %s %s %s\n",msg.staffno,msg.usertype,msg.name,\
				msg.passwd,msg.age,msg.phone,msg.addr,msg.work,msg.date,msg.level,msg.salary);
		printf("--------------------------------------------------------------\n");	
		memset(&msg,0,sizeof(msg));
	}
}
//修改用户函数
void admin_amend(int sockfd)
{
	char buf[N] = {0};
	char staffno[N] = {0};
	int i = 0;
	printf("请输入你要修改的工号(数字):");
	scanf("%s",staffno);
	while(i != 10){
		strcpy(buf,"3.admin_amend:");
		send(sockfd,buf,sizeof(buf),0);
		send(sockfd,staffno,sizeof(staffno),0);
		printf("*************请输入要修改的选项**************\n");
		printf("****** 1:姓名 2:年龄 3:家庭住址 4:电话 ******\n");
		printf("****** 5:职位 6:工资 7:入职年月 8:评级 ******\n");
		printf("****** 9:密码 10:退出                  ******\n");
		printf("*********************************************\n");
		printf("请输入你要修改的选项(数字)>>");
		scanf("%d",&i);
		switch(i){
		case 1:
			send(sockfd,"name",sizeof("name"),0);
			printf("请输入姓名:");
			scanf("%s",buf);
			send(sockfd,buf,sizeof(buf),0);
			break;
		case 2:
			send(sockfd,"age",sizeof("age"),0);
			printf("请输入年龄:");
			scanf("%s",buf);
			send(sockfd,buf,sizeof(buf),0);
			break;
		case 3:
			send(sockfd,"addr",sizeof("addr"),0);
			printf("请输入家庭住址:");
			scanf("%s",buf);
			send(sockfd,buf,sizeof(buf),0);
			break;
		case 4:
			send(sockfd,"phone",sizeof("phone"),0);
			printf("请输入电话:");
			scanf("%s",buf);
			send(sockfd,buf,sizeof(buf),0);
			break;
		case 5:
			send(sockfd,"work",sizeof("work"),0);
			printf("请输入职位:");
			scanf("%s",buf);
			send(sockfd,buf,sizeof(buf),0);
			break;
		case 6:
			send(sockfd,"salary",sizeof("salary"),0);
			printf("请输入工资:");
			scanf("%s",buf);
			send(sockfd,buf,sizeof(buf),0);
			break;
		case 7:
			send(sockfd,"date",sizeof("date"),0);
			printf("请输入入职年月:");
			scanf("%s",buf);
			send(sockfd,buf,sizeof(buf),0);
			break;
		case 8:
			send(sockfd,"level",sizeof("level"),0);
			printf("请输入评级:");
			scanf("%s",buf);
			send(sockfd,buf,sizeof(buf),0);
			break;
		case 9:
			send(sockfd,"passwd",sizeof("passwd"),0);
			printf("请输入密码:");
			scanf("%s",buf);
			send(sockfd,buf,sizeof(buf),0);
			break;
		case 10:
			send(sockfd,"4",sizeof("4"),0);
			break;
		default:
			printf("输入错误请重新输入");
		}
		if(i != 10){
			recv(sockfd,buf,sizeof(buf),0);
			printf("%s\n",buf);
		}
	}
}
//添加用户函数
void admin_add(int sockfd)
{
	char buf[N] = {0};

	printf("***************热烈欢迎新员工***************\n");
	while(1){
		strcpy(buf,"4.insert_user");
		send(sockfd,buf,sizeof(buf),0);
		printf("请输入工号:");
		scanf("%s",msg.staffno);
		printf("您输入的工号是:%s\n",msg.staffno);
		printf("工号信息一旦录入无法更改,请确认您所输入的是否正确(y/n):");
		scanf("%s",buf);
		if(buf[0] != 'y')
			break;
		printf("请输入用户名:");
		scanf("%s",msg.name);
		printf("请输入密码:");
		scanf("%s",msg.passwd);
		printf("请输入年龄:");
		scanf("%s",msg.age);
		printf("请输入电话:");
		scanf("%s",msg.phone);
		printf("请输入家庭住址:");
		scanf("%s",msg.addr);
		printf("请输入职位:");
		scanf("%s",msg.work);
		printf("请输入入职日期:");
		scanf("%s",msg.date);
		printf("请输入评级:");
		scanf("%s",msg.level);
		printf("请输入工资:");
		scanf("%s",msg.salary);
		printf("是否为管理员(y/n):");
		scanf("%s",buf);
		if(buf[0] == 'y'){
			msg.usertype[0] = '0';
		}else{
			msg.usertype[0] = '1';
		}
		send(sockfd,&msg,sizeof(msg),0);
		recv(sockfd,buf,sizeof(buf),0);
		printf("%s",buf);
		scanf("%s",buf);
		if(buf[0] != 'y'){
			break;
		}
	}
}
//删除用户函数
void admin_del(int sockfd)
{
	char staffno[N] = {0};
	char username[N] = {0};
	char buf[N] = {0};
	strcpy(buf,"5.del_user");
	send(sockfd,buf,sizeof(buf),0);
	printf("请输入要删除的用户工号:");
	scanf("%s",staffno);
	send(sockfd,staffno,sizeof(staffno),0);
	printf("请输入要删除的用户名:");
	scanf("%s",username);
	send(sockfd,username,sizeof(username),0);
	recv(sockfd,buf,sizeof(buf),0);
	printf("%s\n",buf);
}
//查询历史函数
void admin_history(int sockfd)
{
	char buf[N] = {0};
	printf("--------admin_history-------\n");
	printf("-------时间----------用户------------操作记录----------------------\n");
	strcpy(buf,"6.admin_history");
	send(sockfd,buf,sizeof(buf),0);
	while(1){
		recv(sockfd,&msg_history,sizeof(msg_history),0);
		if(msg_history.words[0] == '0')
			break;
		printf("%s %s %s\n",msg_history.date,msg_history.name,msg_history.words);
	}
	printf("--------------------------------------------------------------\n");
}
//用户登录界面函数
void user_succeed(int sockfd,char *username)
{
	char buf[N] ={0};
	int i = 0;
	while(i != 3){
		printf("亲爱的 %s 用户,欢迎登录员工管理系统!\n",username);
		printf("***********************************\n");
		printf("* 1.查询用户 2.修改用户 3.退出用户*\n");
		printf("***********************************\n");
		printf("请选择你要进行的操作(数字)>>");
		scanf("%d",&i);
		switch(i){
		case 1:
			strcpy(buf,"1.msg_user");
			send(sockfd,buf,sizeof(buf),0);
			recv(sockfd,&msg,sizeof(msg),0);
			printf("--------------------------------------------------------------\n");
			printf("工号 用户类型 姓名 密码 年龄 电话 地址 职位 入职年月 等级 工资\n");
			printf("%s %s %s %s %s %s %s %s %s %s %s\n",msg.staffno,msg.usertype,msg.name,\
					msg.passwd,msg.age,msg.phone,msg.addr,msg.work,msg.date,msg.level,msg.salary);
			printf("--------------------------------------------------------------\n");
			break;
		case 2:
			//用户修改函数
			user_aiter(sockfd);
			break;
		case 3:
			send(sockfd,"3",sizeof("3"),0);
			break;
		default:
			printf("输入错误请重新输入\n");
		}
	}
}
void user_aiter(int sockfd)
{
	int i = 0;
	char buf[N]= {0};
	while(i != 4){
		strcpy(buf,"2.user_aiter");
		send(sockfd,buf,sizeof(buf),0);
		printf("**请输入要修改的选项(其他信息亲请联系管理员)**\n");
		printf("*      1:家庭住址  2:电话 3:密码 4:退出      *\n");
		printf("**********************************************\n");
		printf("请输入你的选项(数字)>>");
		scanf("%d",&i);
		switch(i){
		case 1:
			send(sockfd,"addr",sizeof("addr"),0);
			printf("请输入你家庭住址:");
			scanf("%s",buf);
			send(sockfd,buf,sizeof(buf),0);
			break;
		case 2:
			send(sockfd,"phone",sizeof("phone"),0);
			printf("请输入你电话:");
			scanf("%s",buf);
			send(sockfd,buf,sizeof(buf),0);
			break;
		case 3:
			send(sockfd,"passwd",sizeof("passwd"),0);
			printf("请输入你密码:");
			scanf("%s",buf);
			send(sockfd,buf,sizeof(buf),0);
			break;
		case 4:
			send(sockfd,"4",sizeof("4"),0);
			break;
		default:
			printf("输入错误请重新输入\n");
		}
		if(i != 4){
			recv(sockfd,buf,sizeof(buf),0);
			printf("%s\n",buf);
			if(i == 3){
				exit(-1);
			}
		}
	}
}

