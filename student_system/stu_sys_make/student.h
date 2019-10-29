#ifndef __STUDENT_H__
#define __STUDENT_H__
typedef struct students
{
	int number;
	struct
	{
		float Chinese;
		float Math;
		float English;
		float Average;
	}score;
}STU;
void type(STU *p);
void ave(STU *p);
void list(STU *p);
void sort(STU *p);
void search(STU *p);
int n ;
STU stu[20];
void help();
#endif