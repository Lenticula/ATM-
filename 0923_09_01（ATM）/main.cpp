#include"stdio.h"
#include"string.h"
#include"stdlib.h"

struct Account
{
	char name[100];
	char IDcard[100];

	char username[100];
	char password[100];
	float money;

	struct Account * next;
};

typedef struct Account Account;

Account * head=NULL;
Account * tail=NULL;

Account *curAccount=NULL;

void drawMoney()
{
	float money;
	printf("请输入取款金额：\n");
	scanf("%f",&money);
	curAccount->money-=money;
}

void saveMoney()
{
	float money;
	printf("请输入存钱的金额:\n");
    scanf("%f",&money);
	curAccount->money+=money;
}

void one()
{
	float deposit=0.0;
    printf("\t\t\t\t\t     您的余额为：%f\n",deposit);
	system("pause");
	system("cls");
}

void zero()
{
    printf("欢迎您再次使用！\n");
}

void menu()
{
	int select;
	while(select!=0)
	{
        printf("\t\t\t\t\t*****欢迎使用!***** \n");
	printf("\t\t\t\t\t     1.查询余额 \n");
    	printf("\t\t\t\t\t     2.取款\n");
	printf("\t\t\t\t\t     3.存款\n");
    	printf("\t\t\t\t\t     0.退出使用\n");
     	printf("\t\t\t\t\t     请输入您的选项：\n");
        scanf("%d",&select);
	system("cls");
	if(select!=0 && select!=1 && select!=2 && select!=3)
	    {
		printf("您输入的选项有误，请重新输入\n");
		continue;
	    }
	switch(select)
	    {
	     	case 1: one();break;
		case 2: drawMoney();break;
		case 3: saveMoney();break;
	    }
	}
	if(select==0)
	{
		zero();
	}

}

int finAccount(Account a)
{
	Account * curP=head;
	while(curP!=NULL)
	{
		if((strcmp(curP->username,a.username)==0)&&(strcmp(curP->password,a.password)==0))
		{
			curAccount = curP;
			return 1;
		
		}
		curP=curP->next;
	}
	return 0;

}

void updatepassword()
{
	char oldpassword[100]={'\0'};
	printf("请输入旧密码：\n");

	scanf("%s",oldpassword);
	if(strcmp(oldpassword,curAccount->password)==0)
	{
		printf("请输入新密码：\n");
		scanf("%s",curAccount->password);
	}
	else
	{
		printf("密码错误，不能修改！\n");
	}

}

void showMenu()
{
	system("cls");
	printf("修改密码请按1：\n");

    updatepassword();

}

void sighIn()
{
	Account a;
	printf("请输入账号：\n");
	scanf("%s",a.username);

    printf("请输入密码：\n");
    scanf("%s",a.password);

	if(finAccount(a))
	{
        printf("登陆成功！\n");
		showMenu();
	}
	else
	{  
		printf("登陆失败！\n");
		int count=0;
        while(count<=3);
		{
              scanf("%s",a.password);
			  if(finAccount(a))
			  {
                  printf("登陆成功！\n");
			  }
			  else
			  {
				  count++;
			  }
		}
        printf("未登录成功，账号已被锁！\n");
	}
}

int loaDate()
{
	FILE * fp=fopen("D:\\atm.txt","r");
	if(fp==NULL)
	{
		return 0;
	}
	else
	{
		while(!feof(fp))
		{
			Account * newNode=(Account *) malloc(sizeof(Account));

			newNode->next=NULL;
			fscanf(fp,"%s %s\n",newNode->username,newNode->password);

			if(head==NULL)
			{
				head=newNode;
				tail=newNode;
			}
			else
			{
				tail->next=newNode;
				tail=newNode;
			}
		}
		fclose(fp);
		return 1;
	}
}

void printLinkedlist()
{
	Account * curP=head;
	while(curP!=NULL)
	{
		printf("%s\t%s\n",curP->username,curP->password);
		curP=curP->next;
	}
}

int main()
{
	int status=loaDate();
	if(status==1)
	{
		printf("加载成功！\n");
	}
	else
	{
        printf("加载失败！\n");
	}

	menu();//主界面菜单

	printLinkedlist();//结点

	sighIn();//登录

    loaDate();//加载

	drawMoney();//取钱

	saveMoney();//存钱

	return 0;

}
