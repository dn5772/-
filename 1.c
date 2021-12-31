#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// #include<termio.h>

#define Enword 16
#define Koword 31
typedef struct Node
{
	char En_word[Enword];
	char Ko_word[Koword];
	struct Node* next;
}Node;

int cnt;
Node *head;
Node *cur;
Node *temp;


Node* makeNode()
{
	Node* node = (Node *)malloc(sizeof(Node));
	node->next = NULL;
	node->En_word[0] = 0;
	node->Ko_word[0] = 0;
	return node;
}


void Sorting()
{
	cur = temp = head;

	for(int i=0;i<cnt;i++)
	{
		for(int j=0;j<cnt-i;j++)
		{
			if(strcmp(temp->En_word, cur->En_word)>0)
			{
				char tem_E[Enword]={0};
				char tem_K[Koword]={0};
				strcpy(tem_E, cur->En_word);
				strcpy(cur->En_word, temp->En_word);
				strcpy(temp->En_word , tem_E);

				strcpy(tem_K, cur->Ko_word);
				strcpy(cur->Ko_word, temp->Ko_word);
				strcpy(temp->Ko_word, tem_K);
			}
			cur = cur->next;
		}
		temp = cur = temp->next;
	}
}



				
void Eng_test();
void menu()
{
	printf(">> 영어 단어 맞추기 프로그램 <<\n");
	printf("1. 영어 단어 맞추기\t  2. 프로그램 종료\n");
	printf("\n번호를 선택하세요: ");
	int input=0; scanf("%d",&input);
	
	while(1)
	{
		switch(input)
		{
			case 1:
				Eng_test();
				break;
			case 2:
				system("clear");
				exit(0);
		}
	}
}


void Eng_test()
{	
	int C_num=0,F_num=0;
	cur = head;
	while(cnt--)
	{	
		printf("%s -> ",cur->Ko_word);
		char input[Koword]={0}; 
		scanf("%s",input);
		if(!strcmp(input,".quit")) break;

		if(!strcmp(cur->En_word,input))
		{
			printf("correct!\n");
			C_num++;
		}else{
			printf("incorrect!\n");
			F_num++;
		}
		cur=cur->next;
	}
	
	if(C_num==0 && F_num==0)
	{		
		printf("당신의 점수는 0.00 점입니다.\n");
	}else{
		printf("당신의 점수는 %.2lf 점입니다.\n", (double)100/(C_num + F_num)*C_num);
	}

	while(getchar()!='\n');
	char in = getchar();
	
	while(1){
		in = getchar();

		if(in=='\n')
		{	
			system("clear");
			menu();
		}
		else{
			printf("다음 단계로 넘어가시려면 엔터를 입력해주세요.\n");
		}
	}
}

int main()
{
	FILE *fp = fopen("dic.txt","r");  
	// rewind(fp); 
	char tmp_eng[Enword];

	while(fscanf(fp,"%s",tmp_eng)==1)
	{
		Node* node = makeNode();
		strcpy(node->En_word,tmp_eng);

		fscanf(fp,"%[^\n]s",node->Ko_word);
		fgetc(fp);

		if(!cnt)
		{
			head=cur=node;
			node->next=NULL;
		}else{	
			node->next=NULL;
			cur->next=node;
			cur = cur->next;
		}
		cnt++;
	}
	
	Sorting();
	menu();

	fclose(fp);
	return 0;
}
