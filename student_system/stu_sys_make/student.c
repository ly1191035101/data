#include<stdio.h>
#include"student.h"
void help()
{
	printf("********************************\n");
	printf("*  学生成绩管理系统(帮助菜单)  *\n");
	printf("********************************\n");
	printf("*    H >> 显示帮助菜单         *\n");
	printf("*    T >> 成绩录入             *\n");
	printf("*    A >> 计算学生平均分       *\n");
	printf("*    L >> 列出成绩表           *\n");
	printf("*    P >> 平均成绩从高到底排序 *\n");
	printf("*    S >> 按学号查询成绩       *\n");
	printf("*    C >> 清屏                 *\n");
	printf("*    Q >> 退出系统             *\n");
	printf("********************************\n");
	printf("*Copyrignh <c>2019.7.20 By 李岩*\n");
	printf("********************************\n");
	printf("命令>");
}
void type(STU *p)
{
	int i;
	printf("请输入人数>");
	scanf("%d",&n);
	if(n != 0)
	{
		printf("请输入%d名学生的成绩:\n",n);
		printf("学号 语文 数学 英语\n");
		for(i = 0; i < n; i++)
		{
			printf("%d:",(i + 1));
			(p + i)->number = i + 1;
			scanf("%f%f%f",&(p+i)->score.Chinese,&(p+i)->score.Math,&(p+i)->score.English);
			(p + i)->score.Average = 0;
		}
	}
	else 
		printf("输入错误\n");
	printf("命令>");
}
void ave(STU *p)
{
	int i;
	if (n != 0)
	{	
		for (i = 0; i < n; i++)
		{	
			(p+i)->score.Average = ((p+i)->score.Chinese + (p+i)->score.Math + (p+i)->score.English)/3;
		}
		printf("平均分以计算，请使用“L”查看\n");
	}
	else
		printf("成绩表为空，请先用T命令添加成绩表\n");
	printf("命令>");
}
void list(STU *p)
{
	int i;
	if (n != 0)
	{
		printf("学号 语文 数学 英语 平均分\n");
		for (i = 0;i < n; i++)
			printf(" %d  %.1f  %.1f %.1f  %.1f\n",(p+i)->number,(p+i)->score.Chinese,(p+i)->score.Math,(p+i)->score.English,(p+i)->score.Average);
	}
	else
		printf("成绩表为空，请先用T命令添加成绩表\n");
	printf("命令>");
}
void sort(STU *p)
{
	int i,j;
	STU st[1];
	if(n!=0)
	{
	for (i = 0; i < n-1; i++)
		for(j = 0;j < n-i-1; j++)
			if ((p+j)->score.Average<(p+j+1)->score.Average)
			{
		  			st[0]=stu[j];
					stu[j]=stu[j+1];
					stu[j+1]=st[0];
			}
	}
	else
		printf("成绩表为空，请先用T命令添加列表\n");
		printf("排序完成，请使用“L”查看\n");
}
void search(STU *p)
{
	int i,j;
	if(n != 0)
	{
		printf("请输入要查询的学号>");
		scanf("%d",&i);
		if (0 < i && i <= n)
		{
			for(j=0;j<n;j++)
			{
				if(i == (p+j)->number)
					printf(" %d   %.1f %.1f  %.1f  %.1f\n",(p+j)->number,(p+j)->score.Chinese,(p+j)->score.Math,(p+j)->score.English,(p+j)->score.Average);
			}
		}
		else
			printf("该学号不存在\n");
	}
	else
		printf("成绩表为空，请先用T命令添加成绩表\n");
	printf("命令>");
}

