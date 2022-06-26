#include"stdio.h"
#include"string.h"
#include"stdlib.h"
#include"time.h"

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
Account * otherAccount=NULL;

struct TransactionRecord
{
    char username[100];
    time_t timestamp;//时间戳 
    int type;//交易类型 0-取钱，1-存钱，2-转出，3-转入
    float amount;

    struct TransactionRecord * next; 
};
typedef struct TransactionRecord TR;

TR * trHead=NULL;
TR * trTail=NULL; 

void one()
{
    float deposit=0.0;
    system("pause");
    system("cls");
    printf("\t\t\t\t\t     您的余额为：%f\n",deposit);
}

void drawMoney()
{
	float money;
	printf("请输入取款金额：\n");
	scanf("%f",&money);

	//从账户里面扣钱 
	if(money>curAccount->money)
	{
		printf("余额不足！\n");
	}
	else
	{
		//记录交易记录 创建结点，赋值初始化，添加结点到链表
		TR * newNode=(TR*)malloc(sizeof(TR));

		curAccount->money=curAccount->money - money;
		printf("取款成功！\n");

		newNode->next=NULL;
		strcpy(newNode->username,curAccount->username);
		newNode->type=0;
		newNode->amount=money;
		newNode->timestamp=time(NULL);

		if(trHead==NULL)
		{
			trHead=newNode;
			trTail=newNode; 
		}
		else
		{
			trTail->next=newNode;
			trTail=newNode;
		}
	}
	money=money-money;
        one();
}

void saveMoney()
{
	float money;
	printf("请输入存钱的金额:\n");

        scanf("%f",&money);
	curAccount->money+=money;
	printf("存款成功！\n");
	money=money+money;
        one();
}

void makeuername()
{


}

void zero()
{
    printf("欢迎您再次使用！\n");
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
    	        FILE* fp=fopen("D:\\atm.txt","w");
		fclose(fp);
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
	scanf("%d",&n);
	if(n==1)
	{
              updatepassword();
	}
	else
	{
	      printf("你输入的选项有误，请重新输入。\n");
	      scanf("%d",&n);
	      if(n==1)
	      {
                   updatepassword();
	      }
	}
}

void sighIn()
{
	Account a;
	printf("请输入账号：\n");
	scanf("%s",a.username);
	if(finAccount(a))
	{
		printf("输入的账户不存在，请重新输入。\n");
	 	scanf("%s",a.username);
		if(finAccount(a))
		{
                     printf("请输入密码：\n");
                     scanf("%s",a.password);
        	     if(finAccount(a))
		     {
                          printf("登陆成功！\n");
	                  showMenu();
		     }
        	     else
		     {  
        	           printf("密码错误,登陆失败！\n");
                           for(int count;count<=3;count++);
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
		      }
                       printf("未登录成功，账号已被锁！\n");
	               zero();
		}
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

void saveTransactionRecord()
{
	FILE* fp=fopen("D:/transation_record.txt","w");
	TR* curP=trHead;
	while(curP!=NULL)
	{
		fprintf(fp,"%s %ld %d %f\n",curP->username,curP->timestamp,curP->type,curP->amount);
		curP=curP->next;
	}
	fclose(fp);
}

int findOtherAccount(char otherUsername[])
{
	Account* curp=head;
	while(curp!=NULL)
	{
		if(strcmp(curp->username,otherUsername)==0)
		{
			otherAccount=curp;
			return 1;
		}
		curp=curp->next;
	}
	return 0;
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

void transfer()
{
	char otherUsername[100];

	printf("请输入对方账户：");
	
	scanf("%s",otherUsername);

	//验证账号的合法性
	if(findOtherAccount(otherUsername))
	{
		float money;

		printf("请输入转账金额：");
		
		scanf("%d",&money);

		//验证金额合法性
		if(curAccount->money>=money)
		{
			//记录转账记录：转出(创建交易记录结点，初始化，添加到链表)
			TR * newNodeOut=(TR*)malloc(sizeof(TR));

			//转账（原账户的钱减少，对方账户的钱增多）
			curAccount->money-=money;
			otherAccount->money+=money;

			//输出提示转账成功
			printf("转账成功！\n");

			newNodeOut->next=NULL;
			strcpy(newNodeOut->username,curAccount->username);
			newNodeOut->type=2;
			newNodeOut->amount=money;
			newNodeOut->timestamp=time(NULL);
			if(trHead==NULL)
			{
				trHead=newNodeOut;
				trTail=newNodeOut; 
			}
			else
			{
				trTail->next=newNodeOut;
				trTail=newNodeOut;
			}

			//记录转账记录：转入
			TR * newNodeIn=(TR*)malloc(sizeof(TR));
		
			newNodeIn->next=NULL;
			strcpy(newNodeIn->username,curAccount->username);
			newNodeIn->type=3;
			newNodeIn->amount=money;
			newNodeIn->timestamp=time(NULL);

			if(trHead==NULL)
			{
				trHead=newNodeIn;
				trTail=newNodeIn; 
			}
			else
			{
				trTail->next=newNodeIn;
				trTail=newNodeIn;
			}
		}
		else
		{
			printf("余额不足!\n");
		}
	}
	else
	{
		printf("账户错误！\n");
	}
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
		printf("\t\t\t\t\t     4.转账\n");
		printf("\t\t\t\t\t     5.开通账户\n");
        	printf("\t\t\t\t\t     0.退出使用\n");
        	printf("\t\t\t\t\t     请输入您的选项：\n");
		scanf("%d",&select);
		system("cls");
		if(select!=0 && select!=1 && select!=2 && select!=3 && select!=4 && select!=5)
		{
			printf("您输入的选项有误，请重新输入\n");
			continue;
		}
		switch(select)
		{
	     	case 1: one();break;
			case 2: drawMoney();break;
			case 3: saveMoney();break;
			case 4: transfer();break;
			case 5: makeuername();break;
		}
	}
	if(select==0)
	{
		zero();
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
        loaDate();//加载

	sighIn();//登录

	menu();//主界面菜单

	printLinkedlist();//结点

	drawMoney();//取钱

	saveMoney();//存钱

        transfer();//转账
	
	saveTransactionRecord();//时间戳

	return 0;

}
