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


typedef int QElemType;
/* ���е�˳��洢�ṹ(������ѭ�����кͷ�ѭ������) */
#define MAXQSIZE 5 /* �����г���(����ѭ�����У������г���Ҫ��1) */
typedef struct
{
	QElemType *base; /* ��ʼ���Ķ�̬����洢�ռ� */
	int front; /* ͷָ��,�����в���,ָ�����ͷԪ�� */
	int rear; /* βָ��,�����в���,ָ�����βԪ�ص���һ��λ�� */
}SqQueue;

/* ����һ���ն���Q */
Status InitQueue(SqQueue *Q)
{ 
	(*Q).base=(QElemType *)malloc(MAXQSIZE*sizeof(QElemType));
	if(!(*Q).base) /* �洢����ʧ�� */
		exit(OVERFLOW);
	(*Q).front=(*Q).rear=0;
	return OK;
}

/* ���ٶ���Q,Q���ٴ��� */
Status DestroyQueue(SqQueue *Q)
{ 
	if((*Q).base)
		free((*Q).base);
	(*Q).base=NULL;
	(*Q).front=(*Q).rear=0;
	return OK;
}

/* ��Q��Ϊ�ն��� */
Status ClearQueue(SqQueue *Q)
{ 
	(*Q).front=(*Q).rear=0;
	return OK;
}

/* ������QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE */
Status QueueEmpty(SqQueue Q)
{ 
	if(Q.front==Q.rear) /* ���пյı�־ */
		return TRUE;
	else
		return FALSE;
}

/* ����Q��Ԫ�ظ���,�����еĳ��� */
int QueueLength(SqQueue Q)
{ 
	return(Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
}

/* �����в���,����e����Q�Ķ�ͷԪ��,������OK,���򷵻�ERROR */
Status GetHead(SqQueue Q,QElemType *e)
{ 
	if(Q.front==Q.rear) /* ���п� */
		return ERROR;
	*e=*(Q.base+Q.front);
	return OK;
}

/* ����Ԫ��eΪQ���µĶ�βԪ�� */
Status EnQueue(SqQueue *Q,QElemType e)
{ 
	if(((*Q).rear+1)%MAXQSIZE==(*Q).front) /* ������ */
		return ERROR;
	(*Q).base[(*Q).rear]=e;
	(*Q).rear=((*Q).rear+1)%MAXQSIZE;
	return OK;
}

/* �����в���,��ɾ��Q�Ķ�ͷԪ��,��e������ֵ,������OK;���򷵻�ERROR */
Status DeQueue(SqQueue *Q,QElemType *e)
{ 
	if((*Q).front==(*Q).rear) /* ���п� */
      return ERROR;
    *e=(*Q).base[(*Q).front];
    (*Q).front=((*Q).front+1)%MAXQSIZE;
    return OK;
}

/* �Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���vi().һ��viʧ��,�����ʧ�� */
Status QueueTraverse(SqQueue Q,void(*vi)(QElemType e))
{
	int i;
	i=Q.front;
	while(i!=Q.rear)
	{
		vi(*(Q.base+i));
		i=(i+1)%MAXQSIZE;
	}
	printf("\n");
	return OK;
}

void printnode(QElemType e)
{
	printf("%d ",e);
}

int main()
{
	SqQueue Q;
	QElemType e;
	InitQueue(&Q);

	printf("length:%d\n",QueueLength(Q));
	printf("empty:%d\n",QueueEmpty(Q));
	EnQueue(&Q,10);
	EnQueue(&Q,20);
	EnQueue(&Q,30);
	printf("length:%d\n",QueueLength(Q));
	printf("empty:%d\n",QueueEmpty(Q));
	QueueTraverse(Q,printnode);
	DeQueue(&Q,&e);
	printf("dequeue:%d\n",e);
	QueueTraverse(Q,printnode);

}

