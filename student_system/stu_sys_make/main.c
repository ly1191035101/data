#include<stdio.h>
#include<stdlib.h>
#include"student.h"
int main(int argc, const char *argv[])
{
	char i;
	help();
	while (i != 'Q')
	{
		scanf("%c",&i);
		switch(i)
		{
		case 'H':
			help();	
			break;
		case 'T':
			type(stu);
			break;
		case 'A':
			ave(stu);
			break;
		case 'L':
			list(stu);
			break;
		case 'P':
			sort(stu);
			break;
		case 'S':
			search(stu);
			break;
		case 'C':
			system("clear");
			help();
			break;
		}
	}
	return 0;
}

