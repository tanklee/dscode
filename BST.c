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

/* ��̬���ұ�(����������)�Ļ�������(8��) */
typedef int ElemType; 
typedef struct BiTNode
{
	ElemType data;
    struct BiTNode *lchild;
	struct BiTNode *rchild;
}BiTNode,*BiTree;


/* �������: ����һ���յĶ�̬���ұ�DT */
Status InitDSTable(BiTree *DT)
{ 
   *DT=NULL;
   return OK;
}

/* ��ʼ����: ��̬���ұ�DT���ڡ��������: ���ٶ�̬���ұ�DT */
void DestroyDSTable(BiTree *DT) 
{ 
	if(*DT) /* �ǿ��� */
	{
		if((*DT)->lchild) /* ������ */
			DestroyDSTable(&(*DT)->lchild); /* ������������ */
		if((*DT)->rchild) /* ���Һ��� */
			DestroyDSTable(&(*DT)->rchild); /* �����Һ������� */
		free(*DT); /* �ͷŸ���� */
		*DT=NULL; /* ��ָ�븳0 */
   }
}


/* 
* �ڸ�ָ��T��ָ�����������еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ�أ�
* �����ҳɹ����򷵻�ָ�������Ԫ�ؽ���ָ��,���򷵻ؿ�ָ��
*/
BiTree SearchBST(BiTree T,ElemType key)
{ 
	if(T==NULL)
		return NULL;
	else if(key==T->data)
		return T;	/* ���ҽ��� */
	else if (key<T->data) /* ���������м������� */
		return SearchBST(T->lchild,key);
	else
		return SearchBST(T->rchild,key); /* ���������м������� */
}


/* 
* �ڸ�ָ��T��ָ�����������еݹ�ز�����ؼ��ֵ���key������Ԫ�أ������� 
* �ɹ�����ָ��pָ�������Ԫ�ؽ�㣬������TRUE������ָ��pָ�����·���� 
* ���ʵ����һ����㲢����FALSE,ָ��fָ��T��˫�ף����ʼ����ֵΪNULL 
*/
Status SearchBST1(BiTree T,ElemType key,BiTree f,BiTree *p) 
{ 
	if(T==NULL) /* ���Ҳ��ɹ� */
	{
		*p=f; /* ��¼���Ҳ��ɹ�ʱ���һ�αȽϽڵ㣬������λ��*/
		return FALSE;
	}else if(key==T->data) /*  ���ҳɹ� */
	{
		*p=T;
		return TRUE;
	}else if(key<T->data)
		return SearchBST1(T->lchild,key,T,p); /* ���������м������� */
	else
		return SearchBST1(T->rchild,key,T,p); /*  ���������м������� */
}


/* 
* ������������T�в����ڹؼ��ֵ���key������Ԫ��ʱ������e������TRUE
* ���򷵻�FALSE
*/
Status InsertBST(BiTree *T, ElemType e)
{ 
	BiTree p,s;
	if(!SearchBST1(*T,e,NULL,&p)) /* ���Ҳ��ɹ� */
	{
		s=(BiTree)malloc(sizeof(BiTNode));
		s->data=e;
		s->lchild=s->rchild=NULL;
		if(!p)	/* ��ǰ��Ϊ�� */
			*T=s; /* ������*sΪ�µĸ���� */
		else if(e<p->data)
			p->lchild=s; /* ������*sΪ���� */
		else
			p->rchild=s; /* ������*sΪ�Һ��� */
		return TRUE;
   } else
		return FALSE; /* �������йؼ�����ͬ�Ľ�㣬���ٲ��� */
}


/* �Ӷ�����������ɾ�����p�����ؽ��������������*/
void Delete(BiTree *p)
{
	BiTree q,s;
	if(!(*p)->rchild) /* ����������ֻ���ؽ���������������ɾ�����Ҷ��Ҳ�ߴ˷�֧�� */
	{
		q=*p;
		*p=(*p)->lchild;
		free(q);
	}else if(!(*p)->lchild) /* ֻ���ؽ����������� */
	{
		q=*p;
		*p=(*p)->rchild;
		free(q);
	}else /* �������������� */
	{
		q=*p;
		s=(*p)->lchild;
		while(s->rchild) /* ת��Ȼ�����ҵ���ͷ���Ҵ�ɾ����ǰ���� */
		{
			q=s;
			s=s->rchild;
		}
		(*p)->data=s->data; /* sָ��ɾ���ģ�ǰ����������ɾ���ǰ����ֵȡ����ɾ����ֵ�� */
		if(q!=*p)
		q->rchild=s->lchild; /* �ؽ�*q�������� */
		else
		q->lchild=s->lchild; /* �ؽ�*q�������� */
		free(s);
   }

}


/* 
* ������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�ؽ��
* ������TRUE�����򷵻�FALSE 
*/
Status DeleteBST(BiTree *T,ElemType key)
{ 
	if(!*T) /* �����ڹؼ��ֵ���key������Ԫ�� */
		return FALSE;
	else
	{
		if(key==(*T)->data) /* �ҵ��ؼ��ֵ���key������Ԫ�� */
			Delete(T);
		else if(key<(*T)->data)
			DeleteBST(&(*T)->lchild,key);
		else
			DeleteBST(&(*T)->rchild,key);
		return TRUE;
	}
}

/* 
* ��ʼ����: ��̬���ұ�DT���ڣ�Visit�ǶԽ�������Ӧ�ú��� *
* �������: ���ؼ��ֵ�˳���DT��ÿ�������ú���Visit()һ��������һ�� 
*/
void TraverseDSTable(BiTree DT)
{ 
	if(DT)
	{
		TraverseDSTable(DT->lchild); /* ��������������� */
		printf("%d ",DT->data);
		TraverseDSTable(DT->rchild); /* ���������������� */
	}
}

void PreOrderTraverse(BiTree T)
{
	BiTree stack[100],p;
	int top=0;
	p=T;
	while(p!=NULL || top>0)
	{
		if(p){
			printf("%d ",p->data);
			stack[++top]=p;
			p=p->lchild;
		}
		else{
			p=stack[top--];
			p=p->rchild;
		}
	}
	printf("\n");
}

void InOrderTraverse(BiTree T)
{
	BiTree stack[100],p;
	int top=0;
	p=T;
	while(p!=NULL || top>0)
	{
		if(p){
			stack[++top]=p;
			p=p->lchild;
		}
		else{
			p=stack[top--];
			printf("%d ",p->data);
			p=p->rchild;
		}
	}
	printf("\n");
}

void PostOrderTraverse(BiTree T)
{
	BiTree stack[100],p,q;
	int top=0;
	p=T;
	q=NULL;
	while(p!=NULL || top>0)
	{
		if(p){
			stack[++top]=p;
			p=p->lchild;
		}
		else{
			p=stack[top];
			if(p->rchild!=NULL && p->rchild!=q)
				p=p->rchild;
			else{
				p=stack[top--];
				printf("%d ",p->data);
				q=p;
				p=NULL;
			}
		}
	}
	printf("\n");
}

void LevelTraverse(BiTree T)
{
	BiTree queue[100],p;
	int front,rear;
	front=rear=0;
	if(T)
	{
		queue[rear++]=T;
		while(rear!=front){
			p=queue[front++];
			printf("%d ",p->data);
			if(p->lchild)
				queue[rear++]=p->lchild;
			if(p->rchild)
				queue[rear++]=p->rchild;
		}
		printf("\n");
	}
	
}

Status JudgeBST(BiTree T)
{
	if(!T)
		return TRUE;
	if(T->lchild && T->lchild->data>=T->data)
		return FALSE;
	if(T->rchild && T->rchild->data<=T->data)
		return FALSE;
	return (JudgeBST(T->lchild)&&JudgeBST(T->rchild));
}


/* 
* ������������T�в����ڹؼ��ֵ���key������Ԫ��ʱ������e������1
* ���򷵻�0
*/
int InsertBST_1(BiTree *T, ElemType e)
{ 
	BiTNode *p,*f,*s;
	f=NULL;	/* f��¼�ϴαȽϵĽڵ�ָ�� */
	p=*T;  /* p�ĳ�ֵָ������ */
	while(p){
		if(p->data==e) /* ��������key���������*/
			return 0;
		f=p;
		if(e<p->data)
			p=p->lchild;
		else 
			p=p->rchild;
	}
	s=(BiTNode *)malloc(sizeof(BiTNode));
	s->data=e;
	s->lchild=s->rchild=NULL;
	if(*T==NULL)
		*T=s;
	else{
		if(e<f->data)
			f->lchild=s;
		else
			f->rchild=s;
	}
	return 1;
}


/* 
* ������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�ؽ��
* ������1�����򷵻�0
*/
int DeleteBST_1(BiTree *T,ElemType e)
{
	BiTNode *p,*q,*f,*s;
	if(*T==NULL)
		return 0;
	f=NULL;//��¼�ϴβ��ҽڵ�ָ��
	p=(*T);//��ǰ���ҽڵ�ָ��
	while(p){
		if(p->data==e)
			break;
		f=p;
		if(e<p->data)
			p=p->lchild;
		else
			p=p->rchild;
	}
	if(p==NULL)//�������û�ҵ�����Ҫɾ����������
		return 0;
	//�ҵ��˷��������
	if(p->lchild==NULL){
		if(f==NULL){
			*T=p->rchild;
		}else{		//ֱ�Ӱ��������ӵ����ڵ�
			if(f->lchild==p)
				f->lchild=p->rchild;
			else
				f->rchild=p->rchild;
		}
		free(p);
	}
	else if(p->rchild==NULL){
		if(f==NULL){
			*T=p->lchild;
		}else{	////ֱ�Ӱ��������ӵ����ڵ�
			if(f->lchild==p)
				f->lchild==p->lchild;
			else
				f->rchild=p->lchild;
		}
		free(p);
	}else{
		q=p;
		s=p->lchild;//���������������½ڵ�s��Ϊ�����ɾ���ڵ㣬qΪs���ڵ�(q�п��ܾ���p)
		while(s->rchild){
			q=s;
			s=s->rchild;
		}
		p->data=s->data;//sΪ��ɾ���ڵ�ǰ��
		if(q!=p)//�ؽ�s������
			q->rchild=s->lchild;
		else
			q->lchild=s->lchild;
		free(s);
	}
	return 1;
}

int main()
{
	int a[8]={15,25,35,85,95,100};
	int i;
	BiTree T;
	InitDSTable(&T);

	for(i=0;i<6;i++)
		InsertBST_1(&T,a[i]);
	
	if(JudgeBST(T))
		printf("BST\n");
	PreOrderTraverse(T);
	InOrderTraverse(T);
	PostOrderTraverse(T);
	LevelTraverse(T);
	printf("delete 35\n");

	DeleteBST_1(&T,15);
	if(JudgeBST(T))
		printf("BST\n");
	PreOrderTraverse(T);
	InOrderTraverse(T);
	PostOrderTraverse(T);
	LevelTraverse(T);


	DestroyDSTable(&T);
	return 0;
}