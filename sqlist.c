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

typedef int ElemType;
/* ���Ա�Ķ�̬����˳��洢�ṹ */
#define LIST_INIT_SIZE 100  /* ���Ա�洢�ռ�ĳ�ʼ������ */
#define LISTINCREMENT 10    /* ���Ա�洢�ռ�ķ������� */
typedef struct
{
	ElemType *elem;		/* �洢�ռ��ַ */
	int length;			/* ��ǰ���� */
	int listsize;		/* ��ǰ����Ĵ洢����(��sizeof(ElemType)Ϊ��λ) */
}SqList;


/* �������������һ���յ�˳�����Ա� */
Status InitList(SqList *L) 
{ 
	(*L).elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!(*L).elem)
		exit(OVERFLOW); /* �洢����ʧ�� */
	(*L).length=0; /* �ձ���Ϊ0 */
	(*L).listsize=LIST_INIT_SIZE; /* ��ʼ�洢���� */
   return OK;
}


/* ��ʼ������˳�����Ա�L�Ѵ��ڡ��������������˳�����Ա�L */
Status DestroyList(SqList *L)
{ 
	free((*L).elem);
	(*L).elem=NULL;
	(*L).length=0;
	(*L).listsize=0;
	return OK;
}


/* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
Status ClearList(SqList *L)
{ 
	(*L).length=0;
	return OK;
}


/* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
Status ListEmpty(SqList L)
{ 
	if(L.length==0)
		return TRUE;
	else
		return FALSE;
}


/* ��ʼ������˳�����Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
int ListLength(SqList L)
{ 
	return L.length;
}

/* 
* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) 
* �����������e����L�е�i������Ԫ�ص�ֵ 
*/
Status GetElem(SqList L,int i,ElemType *e)
{
	if(i<1||i>L.length)
		return ERROR;
	*e=*(L.elem+i-1);
	return OK;
}


/* 
* ��ʼ������˳�����Ա�L�Ѵ��ڣ�compare()������Ԫ���ж�����(����Ϊ1,����Ϊ0) 
* �������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ��
* ������������Ԫ�ز����ڣ��򷵻�ֵΪ0���㷨2.6 
*/
int LocateElem(SqList L,ElemType e,Status(*compare)(ElemType,ElemType))
{
	ElemType *p;
	int i=1; /* i�ĳ�ֵΪ��1��Ԫ�ص�λ�� */
	p=L.elem; /* p�ĳ�ֵΪ��1��Ԫ�صĴ洢λ�� */
	
	while(i<=L.length&&!compare(*p++,e))
		++i;
	if(i<=L.length)
		return i;
	else
		return 0;
}


/*
* ��ʼ������˳�����Ա�L�Ѵ��� 
* �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ���� 
* �������ʧ�ܣ�pre_e�޶��� 
*/
Status PriorElem(SqList L,ElemType cur_e,ElemType *pre_e)
{ 
	int i=2;
	ElemType *p=L.elem+1;
	while(i<=L.length&&*p!=cur_e)
	{
		p++;
		i++;
	}
	if(i>L.length)
		return INFEASIBLE;
	else
	{
		*pre_e=*--p;
		return OK;
	}
}


/* 
* ��ʼ������˳�����Ա�L�Ѵ��� 
* �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣� 
* �������ʧ�ܣ�next_e�޶��� 
*/
Status NextElem(SqList L,ElemType cur_e,ElemType *next_e)
{ 
	int i=1;
	ElemType *p=L.elem;
	while(i<L.length&&*p!=cur_e)
	{
		i++;
		p++;
	}
	if(i==L.length)
		return INFEASIBLE;
	else
	{
		*next_e=*++p;
		return OK;
	}
}


/* 
* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L)+1 *
* �����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1
*/
Status ListInsert(SqList *L,int i,ElemType e) 
{ 
	ElemType *newbase,*q,*p;
	if(i<1||i>(*L).length+1) /* iֵ���Ϸ� */
		return ERROR;
	if((*L).length>=(*L).listsize) /* ��ǰ�洢�ռ�����,���ӷ��� */
	{
		newbase=(ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase)
			exit(OVERFLOW); /* �洢����ʧ�� */
		(*L).elem=newbase; /* �»�ַ */
		(*L).listsize+=LISTINCREMENT; /* ���Ӵ洢���� */
	}
	q=(*L).elem+i-1; /* qΪ����λ�� */
	for(p=(*L).elem+(*L).length-1;p>=q;--p) /* ����λ�ü�֮���Ԫ������ */
		*(p+1)=*p;
	*q=e; /* ����e */
	++(*L).length; /* ����1 */
	return OK;
}


/* 
* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) 
* ���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1 
*/
Status ListDelete(SqList *L,int i,ElemType *e) 
{ 
	ElemType *p,*q;
	if(i<1||i>(*L).length) /* iֵ���Ϸ� */
		return ERROR;
	p=(*L).elem+i-1; /* pΪ��ɾ��Ԫ�ص�λ�� */
	*e=*p; /* ��ɾ��Ԫ�ص�ֵ����e */
	q=(*L).elem+(*L).length-1; /* ��βԪ�ص�λ�� */
	for(++p;p<=q;++p) /* ��ɾ��Ԫ��֮���Ԫ������ */
		*(p-1)=*p;
	(*L).length--; /* ����1 */
	return OK;
}


/* 
* ��ʼ������˳�����Ա�L�Ѵ��� 
* ������������ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ�ܣ������ʧ�� 
* vi()���βμ�'&'��������ͨ������vi()�ı�Ԫ�ص�ֵ 
*/
Status ListTraverse(SqList L,void(*vi)(ElemType *))
{ 
	ElemType *p;
	int i;
	p=L.elem;
	for(i=1;i<=L.length;i++)
		vi(p++);
	printf("\n");
	return OK;
}

void printnode(ElemType *pelem)
{
	printf("%d ",*pelem);
}

int equal(ElemType a,ElemType b)
{
	if(a==b)
		return TRUE;
	else
		return FALSE;;
}

void union_sqlist(SqList *La,SqList Lb)
{
	int la_len,lb_len;
	int i,e;
	la_len=ListLength(*La);
	lb_len=ListLength(Lb);

	for(i=1;i<=lb_len;i++)
	{
		GetElem(Lb,i,&e);
		if(!LocateElem(*La,e,equal))
			ListInsert(La,++la_len,e);
	}
}

void merge_sqlist(SqList La,SqList Lb,SqList *Lc)
{
	int i,j,k,a,b;
	int la_len,lb_len;
	InitList(Lc);
	i=1,j=1,k=0;
	la_len=ListLength(La);
	lb_len=ListLength(Lb);
	while(i<=la_len && j<=lb_len)
	{
		GetElem(La,i,&a);
		GetElem(Lb,j,&b);
		if(a<=b) 
		{
			ListInsert(Lc,++k,a);
			++i;
		}
		else
		{
			ListInsert(Lc,++k,b);
			++j;
		}
	}
	while(i<=la_len)
	{
		GetElem(La,i++,&a);
		ListInsert(Lc,++k,a);
	}
	while(j<=lb_len)
	{
		GetElem(Lb,j++,&b);
		ListInsert(Lc,++k,b);
	}

}

int main()
{
	SqList L,L1,L2;
	int e;
	InitList(&L);
	InitList(&L1);

	printf("empty:%d\n", ListEmpty(L));
	printf("length:%d\n",ListLength(L));

	ListInsert(&L,1,1);
	ListInsert(&L,2,2);
	ListInsert(&L,3,3);

	printf("empty:%d\n", ListEmpty(L));
	printf("length:%d\n",ListLength(L));

	ListTraverse(L,printnode);

	/*
	ListDelete(&L,2,&e);
	printf("delete %d\n",e);
	ListTraverse(L,printnode);
	*/
	PriorElem(L,2,&e);
	printf("2 prior %d\n",e);

	NextElem(L,2,&e);
	printf("2 next %d\n",e);

	printf("equal 10 index %d\n",LocateElem(L,10,equal));


	ListInsert(&L1,1,3);
	ListInsert(&L1,2,5);
	ListInsert(&L1,3,6);
	ListTraverse(L1,printnode);

	
	union_sqlist(&L,L1);
	ListTraverse(L,printnode);
	
/*
	merge_sqlist(L,L1,&L2);
	ListTraverse(L2,printnode);
*/
	DestroyList(&L);
	DestroyList(&L1);
//	DestroyList(&L2);
	return 0;
}

