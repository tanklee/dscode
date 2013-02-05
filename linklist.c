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
/* ���Ա�ĵ�����洢�ṹ */
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;


/* �������������һ���յ����Ա�L */
Status InitList(LinkList *L)
{ 
	*L=(LinkList)malloc(sizeof(struct LNode)); /* ����ͷ���,��ʹLָ���ͷ��� */
	if(!*L) /* �洢����ʧ�� */
		exit(OVERFLOW);
	(*L)->next=NULL; /* ָ����Ϊ�� */
	return OK;
}


/* ��ʼ���������Ա�L�Ѵ��ڡ�����������������Ա�L */
Status DestroyList(LinkList *L)
{ 
	LinkList q;
	while(*L)
	{
		q=(*L)->next;
		free(*L);
		*L=q;
	}
	return OK;
}

/* ��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
Status ClearList(LinkList L) /* ���ı�L */
{ 
	LinkList p,q;
	p=L->next; /* pָ���һ����� */
	while(p) /* û����β */
	{
		q=p->next;
		free(p);
		p=q;
	}
	L->next=NULL; /* ͷ���ָ����Ϊ�� */
	return OK;
}


/* ��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
Status ListEmpty(LinkList L)
{ 
	if(L->next) /* �ǿ� */
		return FALSE;
	else
		return TRUE;
}


/* ��ʼ���������Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
int ListLength(LinkList L)
{ 
	int i=0;
	LinkList p=L->next; /* pָ���һ����� */
	while(p) /* û����β */
	{
		i++;
		p=p->next;
	}
	return i;
}


/* LΪ��ͷ���ĵ������ͷָ�롣����i��Ԫ�ش���ʱ,��ֵ����e������OK,���򷵻�ERROR */
Status GetElem(LinkList L,int i,ElemType *e) /* �㷨2.8 */
{ 
	int j=1; /* jΪ������ */
	LinkList p=L->next; /* pָ���һ����� */
	while(p&&j<i) /* ˳ָ��������,ֱ��pָ���i��Ԫ�ػ�pΪ�� */
	{
		p=p->next;
		j++;
	}
	if(!p||j>i) /* ��i��Ԫ�ز����� */
		return ERROR;
	*e=p->data; /* ȡ��i��Ԫ�� */
	return OK;
}


/* 
* ��ʼ����: ���Ա�L�Ѵ���,compare()������Ԫ���ж�����(����Ϊ1,����Ϊ0) 
* �������: ����L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� 
* ������������Ԫ�ز�����,�򷵻�ֵΪ0 
*/
int LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
{ 
	int i=0;
	LinkList p=L->next;
	while(p)
	{
		i++;
		if(compare(p->data,e)) /* �ҵ�����������Ԫ�� */
		return i;
		p=p->next;
	}
	return 0;
}


/* 
* ��ʼ����: ���Ա�L�Ѵ��� 
* �������: ��cur_e��L������Ԫ��,�Ҳ��ǵ�һ��,����pre_e��������ǰ��, 
*           ����OK;�������ʧ��,pre_e�޶���,����INFEASIBLE 
*/
Status PriorElem(LinkList L,ElemType cur_e,ElemType *pre_e)
{ 
	LinkList q,p=L->next; /* pָ���һ����� */
	while(p->next) /* p��ָ����к�� */
	{
		q=p->next; /* qΪp�ĺ�� */
		if(q->data==cur_e)
		{
			*pre_e=p->data;
			return OK;
		}
		p=q; /* p����� */
	}
	return INFEASIBLE;
}


/* 
* ��ʼ���������Ա�L�Ѵ��� 
* �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣�
*           ����OK;�������ʧ�ܣ�next_e�޶��壬����INFEASIBLE 
*/
Status NextElem(LinkList L,ElemType cur_e,ElemType *next_e)
{ 
	LinkList p=L->next; /* pָ���һ����� */
	while(p->next) /* p��ָ����к�� */
	{
		if(p->data==cur_e)
		{
			*next_e=p->next->data;
			return OK;
		}
		p=p->next;
	}
	return INFEASIBLE;
}


/* �ڴ�ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e */
Status ListInsert(LinkList L,int i,ElemType e) /* �㷨2.9�����ı�L */
{ 
	int j=0;
	LinkList p=L,s;
	while(p&&j<i-1) /* Ѱ�ҵ�i-1����� */
	{
		p=p->next;
		j++;
	}
	if(!p||j>i-1) /* iС��1���ߴ��ڱ� */
		return ERROR;
	s=(LinkList)malloc(sizeof(struct LNode)); /* �����½�� */
	s->data=e; /* ����L�� */
	s->next=p->next;
	p->next=s;
	return OK;
}


/* �ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ��,����e������ֵ */
Status ListDelete(LinkList L,int i,ElemType *e) /* �㷨2.10�����ı�L */
{ 
	int j=0;
	LinkList p=L,q;
	while(p->next&&j<i-1) /* Ѱ�ҵ�i�����,����pָ����ǰ�� */
	{
		p=p->next;
		j++;
	}
	if(!p->next||j>i-1) /* ɾ��λ�ò����� */
		return ERROR;
	q=p->next; /* ɾ�����ͷŽ�� */
	p->next=q->next;
	*e=q->data;
	free(q);
	return OK;
}


/* 
* ��ʼ���������Ա�L�Ѵ��� 
* �������:���ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ��,�����ʧ�� 
*/
Status ListTraverse(LinkList L,void(*vi)(ElemType))
{ 
	/* vi���β�����ΪElemType����bo2-1.c����Ӧ�������β�����ElemType&��ͬ */
	LinkList p=L->next;
	while(p)
	{
		vi(p->data);
		p=p->next;
	}
	printf("\n");
	return OK;
}


void CreateList(LinkList *L,int n)
{
	int i;
	LinkList p;
	*L=(LinkList)malloc(sizeof(LNode));
	(*L)->next=NULL; //create a link with head
	for(i=0;i<n;i++)
	{
		printf("input %d node:\n",i+1);
		p=(LinkList)malloc(sizeof(LNode));
		scanf("%d",&p->data);
		p->next=(*L)->next;
		(*L)->next=p;
	}

}

void printnode(ElemType e)
{
	printf("%d ",e);
}

Status equal(ElemType e1,ElemType e2)
{
	if(e1==e2)
		return TRUE;
	else
		return FALSE;
}
																																												
int main()
{
	LinkList L,L1;
	int e;
	InitList(&L);

	printf("empty;%d\n",ListEmpty(L));
	printf("length;%d\n",ListLength(L));

	ListInsert(L,1,1);
	ListInsert(L,2,2);
	ListInsert(L,3,3);
	printf("empty;%d\n",ListEmpty(L));
	printf("length;%d\n",ListLength(L));
	ListTraverse(L,printnode);

	GetElem(L,2,&e);
	printf("elem 2:%d\n",e);

	printf("2 pos:%d\n",LocateElem(L,20,equal));

	CreateList(&L1,5);
	ListTraverse(L1,printnode);

	DestroyList(&L);
	DestroyList(&L1);
	return 0;
}

