#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define MAX_NAME 10
#define COURSE_NUMBER 3 
typedef struct student
{
	int number;
	char name[MAX_NAME];
	int score[COURSE_NUMBER];
	int sum;
	double average;
	struct student *next;
}STUDENT;
int mainmenu();
int menu1();
int menu2();
int menu3();
int menu4();
int menu5();
int menu7();
STUDENT *creat(int n);
STUDENT *inseartnote(STUDENT *head,STUDENT *p,int num);
STUDENT *deletenu(STUDENT *head,int num);
STUDENT *data_modify(STUDENT *head,int num,int sub_cod,int newscore);
void sum_subject(STUDENT *head,int stu_nu); 
void sum_stu(STUDENT *head,int stu_nu);
void search_num(STUDENT *head);
void search_name(STUDENT *head);
void sumup(STUDENT *head);
void list(STUDENT *head);
void file_out(STUDENT *head);
STUDENT *sort_sum_down(STUDENT *head);
STUDENT *sort_number_up(STUDENT *head);
STUDENT *sort_sum_up(STUDENT *head);
void file_out(STUDENT *head);
int main(int argc, char *argv[]) {
	int mi,stu;//mi为菜单选项，stu为学生数量 
	FILE *scanfdata;//作为从文件中读数据 
	STUDENT *p=0; 
	STUDENT *seart;//作为插入的节点
	int stunu;//作为要删去学生学号 
	int mod_nu,sub_cod,newscore;//要修改学生学号,修改科目代号,修改的程序 
	printf("欢迎来到学生成绩管理系统\n");
	while(1)
	{
	switch(mainmenu())
	{
		case 0:
		  exit(0);break;
		case 1:mi=menu1();
		if(mi==1){
		printf("请输入学生人数:");
		scanf("%d",&stu);
		p=creat(stu);	
		}
		else if(mi==2) 
		{
			//传递链表首地址，学生人数 
		}break;
		/////////////////////////////////////////////////////////////////////////
		case 2:mi=menu2();
		if(mi==1)
		{
			if((seart=malloc(sizeof(STUDENT)))==NULL)
			{
				printf("Fall to creat space");
				exit(0);
			}
			printf("请输入学生学号:");
			scanf("%d",&seart->number);
			getchar();
			printf("姓名:");
			fgets(seart->name,sizeof(seart->name),stdin);
			printf("C语言:");
			scanf("%d",&seart->score[0]);
			getchar();
			printf("JAVA:");
			scanf("%d",&seart->score[1]);
			getchar();
			printf("PYTHON:"); 
			scanf("%d",&seart->score[2]);
			getchar();
			seart->sum=seart->score[0]+seart->score[1]+seart->score[2];
			seart->average=(double)(seart->sum)/3;
			p=inseartnote(p,seart,seart->number);
		}
		if(mi==2)
		{
			printf("请输入要删去学生的学号：");
			scanf("%d",&stunu);
			p=deletenu(p,stunu); 
		}
		if(mi==3)
		{
			printf("请输入要修改的学生学号：");
			scanf("%d",&mod_nu); 
			printf("输入要修改的科目代号(c-1,JAVA-2,PYTHON-3)");
			scanf("%d",&sub_cod); 
			printf("请输入修改的成绩：");
			scanf("%d",&newscore);
			p=data_modify(p,mod_nu,sub_cod,newscore);
		};break;
		//////////////////////////////////////////////////////////////////////////
		case 3:mi=menu3();
		if(mi==1)
		{
			sum_subject(p,stu);
		}
		if(mi==2)
		{
			sum_stu(p,stu);
		};break;
		////////////////////////////////////////////////////////////////////////////
		case 4:mi=menu4();
		if(mi==1)
		{
			p=sort_sum_down(p);
			list(p);
		 } 
		if(mi==2)
		{
			p=sort_sum_up(p);
			list(p);
		}
		if(mi==3)
		{
			p=sort_number_up(p);
			list(p);
		};break; 
		/////////////////////////////////////////////////////////////////////////////
		case 5:mi=menu5();
		if(mi==1)
		{
			search_num(p);
		}
		if(mi==2)
		{
			search_name(p);
		};break;
		///////////////////////////////////////////////////////////////////////////////
		case 6:sumup(p);break;
		////////////////////////////////////////////////////////////////////////////////
		case 7:mi=menu7();
		if(mi==1)
		{
			list(p);
		}
		if(mi==2)
		{
			file_out(p);
		};break;
		/////////////////////////////////////////////////////////////////////////////////
	}
}
	return 0;
}
int mainmenu()
{
	int sel;
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("*           Main Menu               *\n");
	printf("* 1. Input                          *\n");
	printf("* 2. Modify                         *\n");
	printf("* 3. Calculat                       *\n");
	printf("* 4. Sort                           *\n");
	printf("* 5. Query                          *\n");
	printf("* 6. Statistic                      *\n");
	printf("* 7. Output                         *\n");
	printf("* 0. Exit                           *\n");
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("Please enter your choice:");
	scanf("%d",&sel);
	return(sel); 
}
int menu1()
{
	int sel;
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("*           Input Menu              *\n");
	printf("* 1. Input from keyboard            *\n");
	printf("* 2. Input from file                *\n");
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("Please enter your choice:");
	scanf("%d",&sel);
	return(sel); 
}
int menu2()
{
	int sel;
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("*           Modify Menu             *\n");
	printf("* 1. Append                         *\n");
	printf("* 2. Delete                         *\n");
	printf("* 3. Modify                         *\n");
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("Please enter your choice:");
	scanf("%d",&sel);
	return(sel); 
}
int menu3()
{
	int sel;
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("*                   Caculate Menu                               *\n");
	printf("* 1. Caculate total and average score of every course           *\n");
	printf("* 2. Caculate total and average score of every student          *\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Please enter your choice:");
	scanf("%d",&sel);
	return(sel); 
}
int menu4()
{
	int sel;
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("*                   Sort Menu                                   *\n");
	printf("* 1. Sort in desecendint order by total score of every student  *\n");
	printf("* 2. Sort in ascending order by total score of every student    *\n");
	printf("* 3. Sort in ascending order by number                          *\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Please enter your choice:");
	scanf("%d",&sel);
	return(sel); 
}
int menu5()
{
	int sel;
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("*           Query Menu              *\n");
	printf("* 1. Search by number               *\n");
	printf("* 2. Search by name                 *\n");
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("Please enter your choice:");
	scanf("%d",&sel);
	return(sel); 
}
int menu7()
{
	int sel;
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("*           Output Menu             *\n");
	printf("* 1. List record                    *\n");
	printf("* 2. Write to a file                *\n");
	printf("* * * * * * * * * * * * * * * * * * *\n");
	printf("Please enter your choice:");
	scanf("%d",&sel);
	return(sel); 	
}
STUDENT *creat(int n)
{
	STUDENT *p,*q,*head;
	int i=1;
	head=NULL;
	while(i<=n)
	{
		if((p=malloc(sizeof(STUDENT)))==NULL)
		{
			printf("Not able to creat please");
			exit(1);
		}
		printf("请输入学生学号:");
		scanf("%d",&p->number);
		getchar();
		printf("姓名:");
		fgets(p->name,sizeof(p->name),stdin);
		printf("C语言:");
		scanf("%d",&p->score[0]);
		getchar();
		printf("JAVA:");
		scanf("%d",&p->score[1]);
		getchar();
		printf("PYTHON:"); 
		scanf("%d",&p->score[2]);
		getchar();
		p->sum=p->score[0]+p->score[1]+p->score[2];
		p->average=(double)p->sum/3;
		if(head==0)
		{
			head=p;
			q=p;
		} 
		else
		{
			q->next=p;
			q=p;
		}
		i++;
	}
	q->next=0;
	return(head);
}
STUDENT *inseartnote(STUDENT *head,STUDENT *p,int num)
{
	STUDENT *be,*ne;
	if(head==0)
	{
		head=p;
		p->next=0;
		return(head);
	}
	if(((head->number)-(p->number))>=0)
	{
		p->next=head;
		head=p;
		return(head);
	}
	be=ne=head;
	while(ne!=0&&(ne->number-p->number>0))
	{
		be=ne;
		ne=ne->next;
	}
	p->next=ne;
	be->next=p;
	return(head);
}
STUDENT *deletenu(STUDENT *head,int num)
{
	STUDENT *be,*p,*ne;
	if(head==NULL)
	{
		printf("No data to delete!\n");
		return(head);
	}
	if(head->number==num)
	{
		p=head;
		head=p->next;
		free(p);
		return(head);
	} 
		be=p=head;
		while(p->number-num!=0&&p->next!=NULL)
		{
			be=ne;
			ne=ne->next;
		} 
		be->next=ne;
		free(p);
		return(head);
}
STUDENT *data_modify(STUDENT *head,int num,int sub_cod,int newscore)
{
	STUDENT *p;
	p=head;
	if(head==0)
	{
		printf("No data to modify!\n");
		return(head);
	}
	while(p->number!=num&&p->next!=0)
	{
		p=p->next;
	}
	if(p->number==num)
	{
		p->score[sub_cod-1]=newscore;
		p->sum=p->score[0]+p->score[1]+p->score[2];
		p->average=p->sum/3;
		return(head);
	}
	if(p->next==0)
	{
		printf("没有符合条件的数据！\n");
		return(head);
	}
	return(head);
}
void sum_subject(STUDENT *head,int stu_nu)
{
	int sum_C=0,sum_JAVA=0,sum_PYTHON=0;
	if(head==0)
	{
		printf("No data accessable！");
	}
	while(head->next!=0)
	{
		sum_C=sum_C+head->score[0];
		sum_JAVA=sum_JAVA+head->score[1];
		sum_PYTHON=sum_PYTHON+head->score[2];
		head=head->next;
	}
		sum_C=sum_C+head->score[0];
		sum_JAVA=sum_JAVA+head->score[1];
		sum_PYTHON=sum_PYTHON+head->score[2];
		printf("C语言课程总分为%d,平均分为%f.2",sum_C,(float)(sum_C/stu_nu));
		printf("JAVA课程总分为%d,平均分为%f.2",sum_JAVA,(float)(sum_JAVA/stu_nu));
		printf("PYTHON课程总分为%d,平均分为%f.2",sum_PYTHON,(float)(sum_PYTHON/stu_nu));	
}
void sum_stu(STUDENT *head,int stu_nu)
{
	int sum;
	while(head->next!=0)
	{
		sum=head->score[0]+head->score[1]+head->score[2];
		head=head->next;
	}
		sum=head->score[0]+head->score[1]+head->score[2];
		printf("%d  %s\n",head->number,head->name);
		printf("总分：%d    平均分：%f",sum,(float)sum/3);
}
void search_num(STUDENT *head)
{
	int num;
	STUDENT *p;
	p=head;
	printf("请输入要查询的学生学号：");
	scanf("%d",&num);
	while(p!=0)
	{
		if(p->number==num)
		{
			printf("学号：%d  姓名：%s\n",num,p->name);
			printf("C语言：%d JAVA:%d PYTHON:%d\n",p->score[0],p->score[1],p->score[2]);
			printf("总分：%d 平均分：%f.2",p->sum,p->average);
		}
		p=p->next;
	}
	printf("未找到符合要求的数据！");
}
void search_name(STUDENT *head)
{
	char mi[10];
	STUDENT *p;
	p=head;
	printf("请输入要查找的学生姓名：");
	fgets(mi,sizeof(mi),stdin);
	while(p!=0)
	{
		if(strcmp(mi,p->name)==0)
		{
			printf("学号：%d  姓名：%s\n",p->number,p->name);
			printf("C语言：%d JAVA:%d PYTHON:%d\n",p->score[0],p->score[1],p->score[2]);
			printf("总分：%d 平均分：%f.2",p->sum,p->average);
		}
		p=p->next;
	}
} 
void sumup(STUDENT *head)
{
	STUDENT *p;
	int ex,go,mi,six,fall,sum;
	int i=0;
	p=head;
	while(i<=2)
	{
		ex=0;
		go=0;
		mi=0;
		six=0;
		fall=0;
		sum=0;
		while(p!=0)
	{
		if(p->score[i]>=90)
		{
			ex++;
		}
		else if(p->score[i]>=80&&p->score[i]<=89)
		{
			go++;
		}
		else if(p->score[i]>=70&&p->score[i]<=79)
		{
			mi++;
		}
		else if(p->score[i]>=60&&p->score[i]<=69)
		{
			six++;
		}
		else if(p->score[i]>=0&&p->score[i]<=59)
		{
			fall++;
		}
		p=p->next;
	}
		sum=ex+go+mi+six+fall;
		switch(i)
		{
		case 0:printf("C语言：\n");break;
		case 1:printf("JAVA:\n");break;
		case 2:printf("PYTHON:\n");break;
		}
		printf("%%f.1 90-100:%d  ",((float)ex/sum)*100,ex);
		printf("%%f.1 90-100:%d  ",((float)go/sum)*100,go);
		printf("%%f.1 90-100:%d  ",((float)mi/sum)*100,mi);
		printf("%%f.1 90-100:%d  ",((float)six/sum)*100,six);
		printf("%%f.1 90-100:%d  ",((float)fall/sum)*100,fall);
	}
}
void list(STUDENT *head)
{
	STUDENT *p;
	p=head;
	while(p!=0)
	{
		printf("%d     %s\n",p->number,p->name);
		printf("C语言:%d JAVA:%d PYTHON:%d\n",p->score[0],p->score[1],p->score[2]);
		printf("总分:%d 平均分:%lf.1\n",p->sum,p->average);
		printf("\n");
		p=p->next; 
	}
}
STUDENT *sort_sum_down(STUDENT *head)
{
 STUDENT *endpt,*u,*v,*p;     
    u = (STUDENT *)malloc(sizeof(STUDENT));   
    u->next=head;
    head=u;   
    for(endpt=NULL;endpt!=head;endpt=p) 
    {
        for(p=u=head;u->next->next!=endpt;u=u->next)  
        {
            if(u->next->sum< u->next->next->sum)
            {                            
                v=u->next->next;   
                u->next->next=v->next;   
                v->next=u->next;   
                u->next=v;   
                p=u->next->next;   
            } 
        }
    }
    u=head;   
    head=head->next;       
    return p; 
}
STUDENT *sort_number_up(STUDENT *head)
{
 STUDENT *endpt,*u,*v,*p;     
    u = (STUDENT *)malloc(sizeof(STUDENT));   
    u->next=head;
    head=u;   
    for(endpt=NULL;endpt!=head;endpt=p) 
    {
        for(p=u=head;u->next->next!=endpt;u=u->next)  
        {
            if(u->next->number< u->next->next->number)
            {                            
                v=u->next->next;   
                u->next->next=v->next;   
                v->next=u->next;   
                u->next=v;   
                p=u->next->next;   
            } 
        }
    }
    u=head;   
    head=head->next;       
    return head; 
}
STUDENT *sort_sum_up(STUDENT *head)
{
 STUDENT *endpt,*u,*v,*p;     
    u = (STUDENT *)malloc(sizeof(STUDENT));   
    u->next=head;
    head=u;   
    for(endpt=NULL;endpt!=head;endpt=p) 
    {
        for(p=u=head;u->next->next!=endpt;u=u->next)  
        {
            if(u->next->sum> u->next->next->sum)
            {                            
                v=u->next->next;   
                u->next->next=v->next;   
                v->next=u->next;   
                u->next=v;   
                p=u->next->next;   
            } 
        }
     u=head;   
      head=head->next;       
       return head; 
}
void file_out(STUDENT *head)
{
	FILE *out;
	STUDENT *p;
	p=head;
	if((out=fopen("C:\\Users\\lenovo\\Desktop\\c\\学生成绩综合管理系统\\print.txt","w"))==NULL)
	{
		printf("Fail to open file!");
		exit(0);
	}
	for(;p!=0;)
	{
		fprintf(out,"%d  %s\n",p->number,p->name);
		fprintf(out,"C语言：%d JAVA：%d PYTHON：%d\n",p->score[0],p->score[1],p->score[2]);
		fprintf(out,"总分：%d  平均：%d\n",p->sum,p->average);
		p=p->next;
	}
	fclose(out);
}
