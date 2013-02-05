#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int Boolean;

typedef int ElemType;
/*
* ջ����ʽ�洢�ṹ��û�и���ͷ��㣩
* ��ջ��û�и���ͷ�����������޵ĵ�����ջ��ָ�����������׽��ָ��
*/
typedef struct StackNode
{
	ElemType data;
	struct StackNode *next;
}StackNode;
typedef struct{
	StackNode *top;
}LinkStack;
/*
* ע�⣺
* ��LinkStack�ṹ���͵Ķ�����Ϊ�˷����ں��������޸�topָ�뱾��
* ����Ҫ��¼ջ��Ԫ�ظ������ɽ�Ԫ�ظ������Է���LinkStack�����ж��塣
*/

Status InitStack(LinkStack *S)
{
	S->top=NULL;
	return OK;
}

Status DestroyStack(LinkStack *S)
{
	StackNode *p=S->top,*q;
	while(p){
		q=p->next;
		free(p);
		p=q;
	}
	S->top=NULL;
	return OK;
}

Status ClearStack(LinkStack *S)
{
	return DestroyStack(S);
}

Status StackEmpty(LinkStack S)
{
	if(S.top==NULL)
		return TRUE;
	else
		return FALSE;
}

int StackLength(LinkStack S)
{
	StackNode *p=S.top;
	int count=0;
	while(p){
		count++;
		p=p->next;
	}
	return count;
}

Status GetTop(LinkStack S,int *e)
{
	if(S.top==NULL)
		return ERROR;
	*e=S.top->data;
	return OK;
}

Status Push(LinkStack *S,int e)
{
	StackNode *p=(StackNode *)malloc(sizeof(StackNode));
	p->data=e;
	p->next=S->top;
	S->top=p;
	return OK;
}

Status Pop(LinkStack *S,int *e)
{
	if(S->top==NULL)
		return ERROR;
	*e=S->top->data;
	S->top=S->top->next;
	return OK;
}

Status StackTraverse(LinkStack S)
{
	StackNode *p=S.top;
	while(p)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
	return OK;
}

int main()
{
	
	LinkStack S;
	int e;

	InitStack(&S);
	printf("length:%d\n",StackLength(S));
	printf("empty:%d\n",StackEmpty(S));

	Push(&S,1);
	Push(&S,2);
	Push(&S,3);

	printf("length:%d\n",StackLength(S));
	printf("empty:%d\n",StackEmpty(S));
	StackTraverse(S);

	Pop(&S,&e);
	printf("pop %d\n",e);
	StackTraverse(S);

	
	DestroyStack(&S);
	return 0;
}