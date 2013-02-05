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

typedef int SElemType;
/* ջ��˳��洢��ʾ */
#define STACK_INIT_SIZE 100 /* �洢�ռ��ʼ������ */
#define STACKINCREMENT 10	/* �洢�ռ�������� */
typedef struct SqStack
{
	SElemType *base; /* ��ջ����֮ǰ������֮��base��ֵΪNULL */
	SElemType *top;	 /* ջ��ָ�� */
	int stacksize;   /* ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ */
}SqStack; /* ˳��ջ */

/* ����һ����ջS */
Status InitStack(SqStack *S)
{ 
	(*S).base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!(*S).base)
		exit(OVERFLOW); /* �洢����ʧ�� */
	(*S).top=(*S).base;
	(*S).stacksize=STACK_INIT_SIZE;
	return OK;
}


/* ����ջS��S���ٴ��� */
Status DestroyStack(SqStack *S)
{ 
	free((*S).base);
	(*S).base=NULL;
	(*S).top=NULL;
	(*S).stacksize=0;
	return OK;
}


/* ��S��Ϊ��ջ */
Status ClearStack(SqStack *S)
{ 
	(*S).top=(*S).base;
	return OK;
}

/* ��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE */
Status StackEmpty(SqStack S)
{ 
	if(S.top==S.base)
		return TRUE;
	else
		return FALSE;
}

/* ����S��Ԫ�ظ�������ջ�ĳ��� */
int StackLength(SqStack S)
{
	return S.top-S.base;
}


/* ��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR */
Status GetTop(SqStack S,SElemType *e)
{ 
	if(S.top>S.base)
	{
		*e=*(S.top-1);
		return OK;
	}
	else
		return ERROR;
}

/* ����Ԫ��eΪ�µ�ջ��Ԫ�� */
Status Push(SqStack *S,SElemType e)
{ 
	if((*S).top-(*S).base>=(*S).stacksize) /* ջ����׷�Ӵ洢�ռ� */
	{
		(*S).base=(SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!(*S).base)
			exit(OVERFLOW); /* �洢����ʧ�� */
		(*S).top=(*S).base+(*S).stacksize;
		(*S).stacksize+=STACKINCREMENT;
	}
	*((*S).top)++=e;
	return OK;
}

/* ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR */
Status Pop(SqStack *S,SElemType *e)
{ 
	if((*S).top==(*S).base)
		return ERROR;
	*e=*--(*S).top;
	return OK;
}

/* 
* ��ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���visit()
* һ��visit()ʧ�ܣ������ʧ�� 
*/
Status StackTraverse(SqStack S,Status(*visit)(SElemType e))
{ 
	while(S.top>S.base)
		visit(*S.base++);
	printf("\n");
	return OK;
}

Status printnode(SElemType e)
{
	printf("%d ",e);
}

void conversion()
{
	int n,e;
	SqStack S;

	InitStack(&S);
	printf("input n=");
	scanf("%d",&n);
	while(n)
	{
		Push(&S,n%8);
		n=n/8;
	}

	while(!StackEmpty(S))
	{
		Pop(&S,&e);
		printf("%d",e);
	}
	printf("\n");
	DestroyStack(&S);
}

void check()
{
	char ch[100],*p;
	int e;
	SqStack S;
	InitStack(&S);

	printf("input a expression:");
	gets(ch);
	p=ch;
	while(*p)
	{
		switch(*p)
		{
			case '(':
			case '[':	Push(&S,*p++);
						break;
			case ')':
			case ']': 
						if(!StackEmpty(S))
						{
							Pop(&S,&e);
							if(*p==')'&&e!='(' || *p==']'&&e!='[')
							{
								printf("dismatch\n");
								exit(ERROR);
							}
							else
							{
								p++;
								break;
							}

						}
						else
						{
							printf("stack empty no left");
							exit(ERROR);
						}
			default :	p++;
		}
	}

	if(StackEmpty(S))
		printf("match");
	else
		printf("no right");

	DestroyStack(&S);
}

int main()
{
	
	SqStack S;
	int e;

	InitStack(&S);
	printf("length:%d\n",StackLength(S));
	printf("empty:%d\n",StackEmpty(S));

	Push(&S,1);
	Push(&S,2);
	Push(&S,3);

	printf("length:%d\n",StackLength(S));
	printf("empty:%d\n",StackEmpty(S));
	StackTraverse(S,printnode);

	Pop(&S,&e);
	printf("pop %d\n",e);
	StackTraverse(S,printnode);

//	conversion();
	check();
	
	DestroyStack(&S);
	return 0;
}

