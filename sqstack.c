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
/* 栈的顺序存储表示 */
#define STACK_INIT_SIZE 100 /* 存储空间初始分配量 */
#define STACKINCREMENT 10	/* 存储空间分配增量 */
typedef struct SqStack
{
	SElemType *base; /* 在栈构造之前和销毁之后，base的值为NULL */
	SElemType *top;	 /* 栈顶指针 */
	int stacksize;   /* 当前已分配的存储空间，以元素为单位 */
}SqStack; /* 顺序栈 */

/* 构造一个空栈S */
Status InitStack(SqStack *S)
{ 
	(*S).base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!(*S).base)
		exit(OVERFLOW); /* 存储分配失败 */
	(*S).top=(*S).base;
	(*S).stacksize=STACK_INIT_SIZE;
	return OK;
}


/* 销毁栈S，S不再存在 */
Status DestroyStack(SqStack *S)
{ 
	free((*S).base);
	(*S).base=NULL;
	(*S).top=NULL;
	(*S).stacksize=0;
	return OK;
}


/* 把S置为空栈 */
Status ClearStack(SqStack *S)
{ 
	(*S).top=(*S).base;
	return OK;
}

/* 若栈S为空栈，则返回TRUE，否则返回FALSE */
Status StackEmpty(SqStack S)
{ 
	if(S.top==S.base)
		return TRUE;
	else
		return FALSE;
}

/* 返回S的元素个数，即栈的长度 */
int StackLength(SqStack S)
{
	return S.top-S.base;
}


/* 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR */
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

/* 插入元素e为新的栈顶元素 */
Status Push(SqStack *S,SElemType e)
{ 
	if((*S).top-(*S).base>=(*S).stacksize) /* 栈满，追加存储空间 */
	{
		(*S).base=(SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!(*S).base)
			exit(OVERFLOW); /* 存储分配失败 */
		(*S).top=(*S).base+(*S).stacksize;
		(*S).stacksize+=STACKINCREMENT;
	}
	*((*S).top)++=e;
	return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status Pop(SqStack *S,SElemType *e)
{ 
	if((*S).top==(*S).base)
		return ERROR;
	*e=*--(*S).top;
	return OK;
}

/* 
* 从栈底到栈顶依次对栈中每个元素调用函数visit()
* 一旦visit()失败，则操作失败 
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

