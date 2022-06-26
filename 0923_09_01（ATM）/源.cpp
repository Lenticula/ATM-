#define EXAMPLE_MACRO_NAME
#include"stdio.h"
#include"string.h"
#include"stdlib.h"
#include"time.h"
#include"windows.h"


int flagl, flagN;
int userID = 0;
int UserNumber = 0;

struct Account
{
	char name[100];
	char IDcard[100];

	char username[100];
	char password[100];
	float money;
	int flag;

	struct Account* next;
};

typedef struct Account Account;

Account* head = NULL;
Account* tail = NULL;

Account* curAccount = NULL;
Account* otherAccount = NULL;

struct TransactionRecord
{
	char username[100];
	time_t timestamp;//ʱ��� 
	int type;//�������� 0-ȡǮ��1-��Ǯ��2-ת����3-ת��
	float amount;

	struct TransactionRecord* next;
};
typedef struct TransactionRecord TR;

TR* trHead = NULL;
TR* trTail = NULL;

void Updateuserinformation()//�����û���Ϣ
{
	FILE* fp;
	if ((fp = fopen("D:\\atm.txt", "w")) != NULL)
	{
		for (int i = 1;i <= UserNumber;i++)
		{
			fwrite(&Account[i], sizeof(struct Account), 1, fp);
		}
		fclose(fp);
	}
	else
	{
		printf("�û���Ϣ����ʧ�ܡ�\n");
	}
}

void one()
{
	float deposit = 0.0;
	system("pause");
	system("cls");
	printf("\t\t\t\t\t     �������Ϊ��%f\n", deposit);
}

void drawMoney()
{
	float money;
	printf("������ȡ���\n");
	scanf("%f", &money);

	//���˻������Ǯ 
	if (money > curAccount->money)
	{
		printf("���㣡\n");
	}
	else
	{
		//��¼���׼�¼ ������㣬��ֵ��ʼ������ӽ�㵽����
		TR* newNode = (TR*)malloc(sizeof(TR));

		curAccount->money = curAccount->money - money;
		printf("ȡ��ɹ���\n");

		newNode->next = NULL;
		strcpy(newNode->username, curAccount->username);
		newNode->type = 0;
		newNode->amount = money;
		newNode->timestamp = time(NULL);

		if (trHead == NULL)
		{
			trHead = newNode;
			trTail = newNode;
		}
		else
		{
			trTail->next = newNode;
			trTail = newNode;
		}
	}
	money = money - money;
	one();
}

void saveMoney()
{
	float money;
	printf("�������Ǯ�Ľ��:\n");

	scanf("%f", &money);
	curAccount->money += money;
	printf("���ɹ���\n");
	money = money + money;
	one();
}

void makeuername()
{
	Sleep(1000);
	int id = UserNumber + 1;
	while (1)
	{

		for (int i = 0; i < 11; i++)
		{
			Account[id].name[i] = rand() % 9 + 1 + '0';
		}
		Account[id].name[11] = '\0';
		int flag = 0;
		for (int i = 1; i <= username; i++)
		{
			if (strcmp(Account[id].name, Account[i].name) == 0)
			{
				flag = i;
				break;
			}
		}
		if (!flag)break;
	}
	printf("�����ɹ����˻�Ϊ��%s\n", Account[id].name);
	while (1)
	{
		Account[id].d = 2;
		Account[id].flag = 1;
		Account[id].money = 0.01;
		strcpy(Account[id].key, "111111");
		char ss[50], cc[50];
		while (1)
		{
			printf("�������˻����룺");
			strcpy(ss, password());
			if (strlen(ss) != 6)
			{
				printf("�������6λ����������������\n");
				memset(ss, '\0', sizeof(char) * 50);
			}
			else
			{ 
				printf("���ٴ������˻����룺");
				strcpy(cc, password());
				if (strcmp(ss, cc) != 0)
				{
					printf("�������벻һ��\n��������������\n");
					memset(ss, 0, sizeof(ss));
					memset(cc, 0, sizeof(cc));

				}
				else
				{
					strcmp(Account[id].key, ss);
					UserNumber++;
					Updateuserinformation();
					printf("�������óɹ�\n,�����ɹ�\n�����������\n");
					getchar();
					getchar();
					return;
				}
			}

		}
	}
}

void zero()
{
	system("cls");

	printf("��ӭ���ٴ�ʹ�ã�\n");
}

int finAccount(Account a)
{
	Account* curP = head;
	while (curP != NULL)
	{
		if ((strcmp(curP->username, a.username) == 0) && (strcmp(curP->password, a.password) == 0))
		{
			curAccount = curP;
			return 1;

		}
		curP = curP->next;
	}
	return 0;

}

void updatepassword()
{
	char oldpassword[100] = { '\0' };
	printf("����������룺\n");

	scanf("%s", oldpassword);
	if (strcmp(oldpassword, curAccount->password) == 0)
	{
		printf("�����������룺\n");
		scanf("%s", curAccount->password);
		FILE* fp = fopen("D:\\atm.txt", "w");
		fclose(fp);
	}
	else
	{
		printf("������󣬲����޸ģ�\n");
	}

}

void showMenu()
{
	int n;
	system("cls");
	printf("�޸������밴1��\n");
	scanf("%d", &n);
	if (n == 1)
	{
		updatepassword();
	}
	else
	{
		printf("�������ѡ���������������롣\n");
		scanf("%d", &n);
		if (n == 1)
		{
			updatepassword();
		}
	}
}

void sighIn()
{
	Account a;
	printf("�������˺ţ�\n");
	scanf("%s", a.username);
	if (finAccount(a))
	{
		printf("������˻������ڣ����������롣\n");
		scanf("%s", a.username);
		if (finAccount(a))
		{
			printf("���������룺\n");
			scanf("%s", a.password);
			if (finAccount(a))
			{
				printf("��½�ɹ���\n");
				showMenu();
			}
			else
			{
				printf("�������,��½ʧ�ܣ�\n");
				for (int count;count<= 3;count++);
				{
					scanf("%s", a.password);
					if (finAccount(a))
					{
						printf("��½�ɹ���\n");
					}
				}
				printf("δ��¼�ɹ����˺��ѱ�����\n");
				zero();
			}
		}
	}
}

int loaDate()
{
	FILE* fp = fopen("D:\\atm.txt", "r");
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		while (!feof(fp))
		{
			Account* newNode = (Account*)malloc(sizeof(Account));

			newNode->next = NULL;
			fscanf(fp, "%s %s\n", newNode->username, newNode->password);

			if (head == NULL)
			{
				head = newNode;
				tail = newNode;
			}
			else
			{
				tail->next = newNode;
				tail = newNode;
			}
		}
		fclose(fp);
		return 1;
	}
}

void saveTransactionRecord()
{
	FILE* fp = fopen("D:/transation_record.txt", "w");
	TR* curP = trHead;
	while (curP != NULL)
	{
		fprintf(fp, "%s %ld %d %f\n", curP->username, curP->timestamp, curP->type, curP->amount);
		curP = curP->next;
	}
	fclose(fp);
}

int findOtherAccount(char otherUsername[])
{
	Account* curp = head;
	while (curp != NULL)
	{
		if (strcmp(curp->username, otherUsername) == 0)
		{
			otherAccount = curp;
			return 1;
		}
		curp = curp->next;
	}
	return 0;
}

void printLinkedlist()
{
	Account* curP = head;
	while (curP != NULL)
	{
		printf("%s\t%s\n", curP->username, curP->password);
		curP = curP->next;
	}
}

void transfer()
{
	char otherUsername[100];

	printf("������Է��˻���");

	scanf("%s", otherUsername);

	//��֤�˺ŵĺϷ���
	if (findOtherAccount(otherUsername))
	{
		float money;

		printf("������ת�˽�");

		scanf("%d", &money);

		//��֤���Ϸ���
		if (curAccount->money >= money)
		{
			//��¼ת�˼�¼��ת��(�������׼�¼��㣬��ʼ������ӵ�����)
			TR* newNodeOut = (TR*)malloc(sizeof(TR));

			//ת�ˣ�ԭ�˻���Ǯ���٣��Է��˻���Ǯ���ࣩ
			curAccount->money -= money;
			otherAccount->money += money;

			//�����ʾת�˳ɹ�
			printf("ת�˳ɹ���\n");

			newNodeOut->next = NULL;
			strcpy(newNodeOut->username, curAccount->username);
			newNodeOut->type = 2;
			newNodeOut->amount = money;
			newNodeOut->timestamp = time(NULL);
			if (trHead == NULL)
			{
				trHead = newNodeOut;
				trTail = newNodeOut;
			}
			else
			{
				trTail->next = newNodeOut;
				trTail = newNodeOut;
			}

			//��¼ת�˼�¼��ת��
			TR* newNodeIn = (TR*)malloc(sizeof(TR));

			newNodeIn->next = NULL;
			strcpy(newNodeIn->username, curAccount->username);
			newNodeIn->type = 3;
			newNodeIn->amount = money;
			newNodeIn->timestamp = time(NULL);

			if (trHead == NULL)
			{
				trHead = newNodeIn;
				trTail = newNodeIn;
			}
			else
			{
				trTail->next = newNodeIn;
				trTail = newNodeIn;
			}
		}
		else
		{
			printf("����!\n");
		}
	}
	else
	{
		printf("�˻�����\n");
	}
}

void menu()
{
	int select;
	while (select != 0)
	{
		printf("\t\t\t\t\t*****��ӭʹ��!***** \n");
		printf("\t\t\t\t\t     1.��ѯ��� \n");
		printf("\t\t\t\t\t     2.ȡ��\n");
		printf("\t\t\t\t\t     3.���\n");
		printf("\t\t\t\t\t     4.ת��\n");
		printf("\t\t\t\t\t     5.��ͨ�˻�\n");
		printf("\t\t\t\t\t     0.�˳�ʹ��\n");
		printf("\t\t\t\t\t     ����������ѡ�\n");
		scanf("%d", &select);
		system("cls");
		if (select != 0 && select != 1 && select != 2 && select != 3 && select != 4 && select != 5)
		{
			printf("�������ѡ����������������\n");
			continue;
		}
		switch (select)
		{
		case 1: one();break;
		case 2: drawMoney();break;
		case 3: saveMoney();break;
		case 4: transfer();break;
		case 5: makeuername();break;
		}
	}
	if (select == 0)
	{
		zero();
	}

}

int main()
{
	int status = loaDate();
	if (status == 1)
	{
		printf("���سɹ���\n");
	}
	else
	{
		printf("����ʧ�ܣ�\n");
	}
	loaDate();//����

	sighIn();//��¼

	menu();//������˵�

	printLinkedlist();//���

	drawMoney();//ȡǮ

	saveMoney();//��Ǯ

	transfer();//ת��

	saveTransactionRecord();//ʱ���

	return 0;

}