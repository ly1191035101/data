#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <linux/in.h>  //sockaddr_in
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

#define N 128
void login_in();
void user_succeed_msg();
void admin_succeed_find_name();
void admin_succeed_all_find();
void admin_amend();
void admin_del_user();
void admin_history();
void admin_insert_user();
void user_amend();
void date_history(char *works);
int admin_name_find_callback(void *arg,int f_num,char **f_value,char **f_name);
int callback(void *arg,int f_num,char **f_value,char **f_name);
int admin_all_find_callback(void *arg,int f_num,char **f_value,char **f_name);
int user_succeed_msg_callback(void *arg,int f_num,char **f_value,char **f_name);
int admin_history_callback(void *arg,int f_num,char **f_value,char **f_name);
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
	char works[N];
}msg_history;
//接收的用户名密码
char username[N] = {0};
char password[N] = {0};
char usertype[N] = {0};
int acceptfd,decide;
sqlite3 *db;
void handler(int signum)
{
	waitpid(-1,NULL,WNOHANG);//非阻塞
}
int main(int argc, const char *argv[])
{
	//判断 是否输入 ip地址 和端口号
	if(argc < 3)
	{
		printf("please input %s and ip and port\n",argv[0]);
		exit(-1);
	}
	//1) socket(),创建套接字文件，用于连接
	int sockfd;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
	{
		perror("socket failed.");
		exit(-1);
	}
	//填充结构体sockaddr_in 
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;            //填充协议 IPv4
	serveraddr.sin_port = htons(atoi(argv[2]));  // 端口号 ,atoi()字符串转整形
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);  //IP

	socklen_t addrlen = sizeof(serveraddr);

	//2) bind(),绑定，把socket()函数返回的文件描述符和IP、端口号进行绑定;
	if(bind(sockfd,(struct sockaddr *)&serveraddr,addrlen) < 0)
	{
		perror("bind failed.");
		exit(-1);
	}
	//3) listen(), (监听)将socket()返回的文件描述符的属æ§，由主动变为被动;
	if(listen(sockfd,8) < 0)
	{
		perror("bind failed.");
		exit(-1);
	}
	//注册一个信号 
	signal(SIGCHLD,handler);
	//4) accept(), 阻塞函数，阻塞等待å¢户端的连接请求，如果有客户端连接，
	//则accept()函数返回的文件描述符和数返回，返回一个用于通信的套接字文件;
	while(1)
	{
		acceptfd = accept(sockfd,NULL,NULL);
		int recvbytes;
		pid_t pid;
		pid = fork();
		if(pid < 0)
		{
			perror("fork failed.");
			exit(-1);
		}
		if(pid == 0)//子进程只用来接受数据
		{
			close(sockfd);
			while(1)
			{
				//5) recv(), 接收客户端发来的数据;   read()
				recvbytes = recv(acceptfd,(void *)usertype,sizeof(usertype),0);
				recvbytes = recv(acceptfd,(void *)username,sizeof(username),0);
				recvbytes = recv(acceptfd,(void *)password,sizeof(password),0);
				//	recvbytes = recv(acceptfd,(void *)buf,sizeof(buf),MSG_DONTWAIT);
				if(recvbytes < 0){
					printf("recv failed.\n");
				}else if(recvbytes == 0){
					break;
				}else{
					printf("------usertype:%s------user:%s------password:%s------\n",\
							(char *)usertype,(char *)username,(char *)password);	
					//登录用户名密码函数
					login_in();
				}
			}
			close(acceptfd);
			exit(-1);
		}
		close(acceptfd);
	}
	close(acceptfd);
	close(sockfd);
	return 0;
}
//登录用户名密码函数
void login_in()
{
	int ret;
	printf("--------------admin_user_pattern---------------\n");
	//打开数据库
	char *errmsg = NULL;
	if(sqlite3_open("staff_manage_system.db",&db) != 0){
		fprintf(stderr, "sqlite3_open failed:%s\n",sqlite3_errmsg(db));
	}
	printf("-------------数据库打开成功-------------\n");	
	char buf[N] = {0};
	sprintf(buf,"select * from usrinfo where usertype = %s and name = '%s' and passwd = '%s';",\
			(char *)usertype,(char *)username,(char *)password);
	printf("%s\n",buf);
	decide = 0;
	ret = sqlite3_exec(db,buf,callback,(void *)decide,&errmsg);
	//判断sqlite3_exec()是否执行成功
	if(ret != 0){
		printf("sqlite3_exec is failed_01\n");
		send(acceptfd,(char *)usertype,sizeof(usertype),0);
	}
	//判断用户名密码是否正确
	if(decide < 1){
		strcpy(buf,"用户名密码错误");
		send(acceptfd,buf,sizeof(buf),0);
	}
}
//sqlite3_exec()登录回调函数
int callback(void *arg,int f_num,char **f_value,char **f_name)
{
	int i;
	char buf[N] = {0};
	if(f_value[1]!=""){
		decide += 1;
	}
	printf("--------------------------------------------------------------\n");
	if(usertype[0] == '0'){
		strcpy(buf,"admin succeed is ok");
		send(acceptfd,buf,sizeof(buf),0);
		//打印登录成功信息
		printf("admin_name:%s---admin_password:%s---%s\n",f_value[2],f_value[3],buf);
		//接受参数
		while(1){
			recv(acceptfd,buf,sizeof(buf),0);
			printf("%s\n",buf);
			switch(buf[0]){
			case '1':
				//按人名查找函数
				admin_succeed_find_name();
				break;
			case '2':
				//查找所有函数
				admin_succeed_all_find();
				break;
			case '3':
				//修改用户函数
				admin_amend();
				break;
			case '4':
				//插入新员工函数
				admin_insert_user();
				break;
			case '5':
				//删除用户
				admin_del_user();
				break;
			case '6':
				//查询历史函数
				admin_history();
				break;
			}
			if(buf[0]== '7'){
				break;
			}
		}
	}else{
		strcpy(buf,"user succeed is ok");
		send(acceptfd,buf,sizeof(buf),0);
		while(1){
			recv(acceptfd,buf,sizeof(buf),0);
			printf("%s\n",buf);
			switch(buf[0]){
			case '1':
				//用户信息查询
				user_succeed_msg();
				break;
			case '2':
				//用户修改函数
				user_amend();
				break;
			}
			if(buf[0]=='3'){
				break;
			}
		}
	}
	return 0;
}
//1.按人名查找函数
void admin_succeed_find_name()
{
	char buf[N] = {0};
	char name[N] = {0};
	int ret;
	char *errmsg = NULL;
	recv(acceptfd,name,sizeof(name),0);
	//打印接收的姓名
	//	printf("%s\n",name);
	sprintf(buf,"select * from usrinfo where name = '%s';",(char *)name);
	printf("%s\n",buf);
	decide = 0;
	ret = sqlite3_exec(db,buf,admin_name_find_callback,NULL,&errmsg);
	//判断sqlite3_exec()是否执行成功
	if(ret != 0){
		printf("sqlite3_exec is failed_02\n");
		send(acceptfd,(char *)usertype,sizeof(usertype),0);
	}
	//判断用户名是否存在
	if(decide < 1){
		strcpy(buf,"n.用户名不存在");
		printf("%s\n",buf);
		send(acceptfd,buf,sizeof(buf),0);
	}
}
//按人名查找回调函数
int admin_name_find_callback(void *arg,int f_num,char **f_value,char **f_name)
{
	int i;
	char buf[N] = {0};
	if(f_value[1] != ""){
		decide += 1;
	}
	printf("--------------------------------------------------------------\n");
	strcpy(msg.staffno,f_value[0]);
	strcpy(msg.usertype,f_value[1]);
	strcpy(msg.name,f_value[2]);
	strcpy(msg.passwd,f_value[3]);
	strcpy(msg.age,f_value[4]);
	strcpy(msg.phone,f_value[5]);
	strcpy(msg.addr,f_value[6]);
	strcpy(msg.work,f_value[7]);
	strcpy(msg.date,f_value[8]);
	strcpy(msg.level,f_value[9]);
	strcpy(msg.salary,f_value[10]);
	send(acceptfd,&msg,sizeof(msg),0);
	printf("工号 用户类型 姓名 密码 年龄 电话 地址 职位 入职年月 等级 工资\n");
	printf("%s %s %s %s %s %s %s %s %s %s %s\n",msg.staffno,msg.usertype,msg.name,\
			msg.passwd,msg.age,msg.phone,msg.addr,msg.work,msg.date,msg.level,msg.salary);
	printf("--------------------------------------------------------------\n");
	return 0;
}
//查询所有用户函数
void admin_succeed_all_find()
{
	char buf[N] = {0};
	int ret;
	char *errmsg = NULL;
	ret = sqlite3_exec(db,"select * from usrinfo;",
			admin_all_find_callback,NULL,&errmsg);
	if(ret != 0){
		printf("sqlite3_exec is failed_03\n");
		send(acceptfd,(char *)usertype,sizeof(usertype),0);
	}
	msg.salary[0] = 'q'; 
	send(acceptfd,&msg,sizeof(msg),0);
}
//查询所有用户回调函数
int admin_all_find_callback(void *arg,int f_num,char **f_value,char **f_name)
{
	int i;
	printf("==============================================================\n");
	strcpy(msg.staffno,f_value[0]);
	strcpy(msg.usertype,f_value[1]);
	strcpy(msg.name,f_value[2]);
	strcpy(msg.passwd,f_value[3]);
	strcpy(msg.age,f_value[4]);
	strcpy(msg.phone,f_value[5]);
	strcpy(msg.addr,f_value[6]);
	strcpy(msg.work,f_value[7]);
	strcpy(msg.date,f_value[8]);
	strcpy(msg.level,f_value[9]);
	strcpy(msg.salary,f_value[10]);
	printf("工号 用户类型 姓名 密码 年龄 电话 地址 职位 入职年月 等级 工资\n");
	printf("%s %s %s %s %s %s %s %s %s %s %s\n",msg.staffno,msg.usertype,msg.name,\
			msg.passwd,msg.age,msg.phone,msg.addr,msg.work,msg.date,msg.level,msg.salary);
	printf("==============================================================\n");
	send(acceptfd,&msg,sizeof(msg),0);
	return 0;
}
//修改用户函数
void admin_amend()
{
	int ret;
	char staffno[N] = {0};
	char type[N] = {0};
	char new[N] = {0};
	char buf[N] = {0};
	char *errmsg = NULL;
	//接受到的工号
	recv(acceptfd,staffno,sizeof(staffno),0);
	//接受需要被修改内容
	recv(acceptfd,type,sizeof(type),0);
	if(type[0]!='4'){
		//接受新的内容
		recv(acceptfd,new,sizeof(new),0);
		sprintf(buf,"update usrinfo set %s = '%s' where staffno = %s;",type,new,staffno);
		printf("%s\n",buf);
		ret = sqlite3_exec(db,buf,NULL,NULL,&errmsg);
		if(ret != 0){		
			printf("sqlite3_exec is failed_04\n");
			strcpy(buf,"数据库修改失败");
			send(acceptfd,buf,sizeof(buf),0);
		}else{
			sprintf(buf,"%s修改%s为%s",username,type,new);
			date_history(buf);
			strcpy(buf,"数据库修改成功");
			send(acceptfd,buf,sizeof(buf),0);
		}
	}
}
//插入新员工
void admin_insert_user(){
	int ret;
	char buf[N] = {0};
	char *errmsg = NULL;
	recv(acceptfd,&msg,sizeof(msg),0);
	sprintf(buf,"insert into usrinfo values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s');",msg.staffno,msg.usertype,msg.name,\
			msg.passwd,msg.age,msg.phone,msg.addr,msg.work,msg.date,msg.level,msg.salary);
	printf("%s\n",buf);
	ret = sqlite3_exec(db,buf,NULL,NULL,&errmsg);
	if(ret != 0){
		printf("sqlite3_exec is failed_05\n");

		strcpy(buf,"2.数据库添加失败");
		send(acceptfd,buf,sizeof(buf),0);
	}else{	
		printf("==============================================================\n");
		printf("工号 用户类型 姓名 密码 年龄 电话 地址 职位 入职年月 等级 工资\n");
		printf("%s %s %s %s %s %s %s %s %s %s %s\n",msg.staffno,msg.usertype,msg.name,\
				msg.passwd,msg.age,msg.phone,msg.addr,msg.work,msg.date,msg.level,msg.salary);
		printf("==============================================================\n");
		sprintf(buf,"%s添加了用户%s",username,msg.name);
		date_history(buf);
		memset(&msg,0,sizeof(msg));
		strcpy(buf,"数据库添加成功,是否继续添加员工(y/n):");	
		send(acceptfd,buf,sizeof(buf),0);
	}
}
//用户查询函数

void user_succeed_msg()
{
	int ret;
	char *errmsg = NULL;
	char buf[N] = {0};
	sprintf(buf,"select * from usrinfo where usertype = %s and name = '%s' and passwd = '%s';",\
			(char *)usertype,(char *)username,(char *)password);
	printf("%s\n",buf);
	ret = sqlite3_exec(db,buf,user_succeed_msg_callback,NULL,&errmsg);
	if(ret != 0){
		printf("sqlite3_exec is failed_06\n");
	}
}
//用户信息回调函数
int user_succeed_msg_callback(void *arg,int f_num,char **f_value,char **f_name)
{
	int i;
	printf("==============================================================\n");
	strcpy(msg.staffno,f_value[0]);
	strcpy(msg.usertype,f_value[1]);
	strcpy(msg.name,f_value[2]);
	strcpy(msg.passwd,f_value[3]);
	strcpy(msg.age,f_value[4]);
	strcpy(msg.phone,f_value[5]);
	strcpy(msg.addr,f_value[6]);
	strcpy(msg.work,f_value[7]);
	strcpy(msg.date,f_value[8]);
	strcpy(msg.level,f_value[9]);
	strcpy(msg.salary,f_value[10]);
	printf("工号 用户类型 姓名 密码 年龄 电话 地址 职位 入职年月 等级 工资\n");
	printf("%s %s %s %s %s %s %s %s %s %s %s\n",msg.staffno,msg.usertype,msg.name,\
			msg.passwd,msg.age,msg.phone,msg.addr,msg.work,msg.date,msg.level,msg.salary);
	printf("==============================================================\n");
	send(acceptfd,&msg,sizeof(msg),0);
	return 0;
}
//删除用户
void admin_del_user()
{
	int ret;
	char *errmsg = NULL;
	char buf[N] = {0};
	char staffno[N] = {0};
	char name[N] = {0};
	recv(acceptfd,staffno,sizeof(staffno),0);
	recv(acceptfd,name,sizeof(name),0);
	sprintf(buf,"delete from usrinfo where staffno = %s and name = '%s';",staffno,name);
	printf("%s\n",buf);
	ret = sqlite3_exec(db,buf,NULL,NULL,&errmsg);
	if(ret != 0){
		printf("sqlite3_exec is failed_06\n");
		sprintf(buf,"删除工号:%s用户:%s失败",staffno,name);
		send(acceptfd,buf,sizeof(buf),0);
	}else{
		sprintf(buf,"%s删除了用户%s",username,msg.name);
		date_history(buf);
		sprintf(buf,"删除工号:%s用户:%s成功",staffno,name);
		send(acceptfd,buf,sizeof(buf),0);
	}
}
//查询历史函数
void admin_history()
{
	char buf[N] = {0};
	int ret;
	char *errmsg = NULL;
	printf("-------时间----------用户------------操作记录----------------------\n");
	ret = sqlite3_exec(db,"select * from historyinfo;",
			admin_history_callback,NULL,&errmsg);
	if(ret != 0){
		printf("sqlite3_exec is failed_07\n");
		send(acceptfd,(char *)usertype,sizeof(usertype),0);
	}
	msg_history.works[0] = '0'; 
	printf("--------------------------------------------------------------\n");
	send(acceptfd,&msg_history,sizeof(msg_history),0);
}
int admin_history_callback(void *arg,int f_num,char **f_value,char **f_name)
{
	strcpy(msg_history.date,f_value[0]);
	strcpy(msg_history.name,f_value[1]);
	strcpy(msg_history.works,f_value[2]);
	send(acceptfd,&msg_history,sizeof(msg_history),0);
	printf("%s %s %s\n",msg_history.date,msg_history.name,msg_history.works);
	return 0;
}
void date_history(char *works)
{
	char date[N] = {0};
	char buf[256]={0};
	int ret;
	char *errmsg = NULL;
	time_t tm;
	struct tm *tmm;
	tm = time(NULL);
	tmm = localtime(&tm);
	sprintf(date,"%d-%d-%d %d:%d:%d",tmm->tm_year+1900,tmm->tm_mon+1,\
			tmm->tm_mday,tmm->tm_hour,tmm->tm_min,tmm->tm_sec);
	sprintf(buf,"insert into historyinfo values('%s','%s','%s');",date,username,works);
	printf("%s\n",buf);
	ret = sqlite3_exec(db,buf,NULL,NULL,&errmsg);
	if(ret != 0){
		printf("sqlite3_exec is failed_08\n");
	}
}
//用户信息修改
void user_amend()
{
	int ret;
	char *errmsg = NULL;
	char type[N] = {0};
	char new[N] = {0};
	char buf[N] = {0};
	//接受需要被修改内容
	recv(acceptfd,type,sizeof(type),0);
	printf("%s",type);
	if(type[0]!='4'){
		//接受新的内容
		recv(acceptfd,new,sizeof(new),0);
		sprintf(buf,"update usrinfo set %s = '%s' where name = '%s';",type,new,username);
		printf("%s\n",buf);
		ret = sqlite3_exec(db,buf,NULL,NULL,&errmsg);
		if(ret != 0){		
			printf("sqlite3_exec is failed_09\n");
			strcpy(buf,"数据库修改失败");
			send(acceptfd,buf,sizeof(buf),0);
		}else{
			sprintf(buf,"%s 将 %s 修改为 %s",username,type,new);
			date_history(buf);
			if(type[0]!='p'){
				send(acceptfd,buf,sizeof(buf),0);
			}else{
				sprintf(buf,"%s 将 %s 修改为 %s",username,type,new);
				date_history(buf);
				sprintf(buf,"%s,密码修改成功,请重新登录",username);
				send(acceptfd,buf,sizeof(buf),0);
			}
		}
	}
}

