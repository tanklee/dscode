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

/* 动态查找表(二叉排序树)的基本操作(8个) */
typedef int ElemType; 
typedef struct BiTNode
{
	ElemType data;
    struct BiTNode *lchild;
	struct BiTNode *rchild;
}BiTNode,*BiTree;


/* 操作结果: 构造一个空的动态查找表DT */
Status InitDSTable(BiTree *DT)
{ 
   *DT=NULL;
   return OK;
}

/* 初始条件: 动态查找表DT存在。操作结果: 销毁动态查找表DT */
void DestroyDSTable(BiTree *DT) 
{ 
	if(*DT) /* 非空树 */
	{
		if((*DT)->lchild) /* 有左孩子 */
			DestroyDSTable(&(*DT)->lchild); /* 销毁左孩子子树 */
		if((*DT)->rchild) /* 有右孩子 */
			DestroyDSTable(&(*DT)->rchild); /* 销毁右孩子子树 */
		free(*DT); /* 释放根结点 */
		*DT=NULL; /* 空指针赋0 */
   }
}


/* 
* 在根指针T所指二叉排序树中递归地查找某关键字等于key的数据元素，
* 若查找成功，则返回指向该数据元素结点的指针,否则返回空指针
*/
BiTree SearchBST(BiTree T,ElemType key)
{ 
	if(T==NULL)
		return NULL;
	else if(key==T->data)
		return T;	/* 查找结束 */
	else if (key<T->data) /* 在左子树中继续查找 */
		return SearchBST(T->lchild,key);
	else
		return SearchBST(T->rchild,key); /* 在右子树中继续查找 */
}


/* 
* 在根指针T所指二叉排序树中递归地查找其关键字等于key的数据元素，若查找 
* 成功，则指针p指向该数据元素结点，并返回TRUE，否则指针p指向查找路径上 
* 访问的最后一个结点并返回FALSE,指针f指向T的双亲，其初始调用值为NULL 
*/
Status SearchBST1(BiTree T,ElemType key,BiTree f,BiTree *p) 
{ 
	if(T==NULL) /* 查找不成功 */
	{
		*p=f; /* 记录查找不成功时最后一次比较节点，即插入位置*/
		return FALSE;
	}else if(key==T->data) /*  查找成功 */
	{
		*p=T;
		return TRUE;
	}else if(key<T->data)
		return SearchBST1(T->lchild,key,T,p); /* 在左子树中继续查找 */
	else
		return SearchBST1(T->rchild,key,T,p); /*  在右子树中继续查找 */
}


/* 
* 当二叉排序树T中不存在关键字等于key的数据元素时，插入e并返回TRUE
* 否则返回FALSE
*/
Status InsertBST(BiTree *T, ElemType e)
{ 
	BiTree p,s;
	if(!SearchBST1(*T,e,NULL,&p)) /* 查找不成功 */
	{
		s=(BiTree)malloc(sizeof(BiTNode));
		s->data=e;
		s->lchild=s->rchild=NULL;
		if(!p)	/* 当前树为空 */
			*T=s; /* 被插结点*s为新的根结点 */
		else if(e<p->data)
			p->lchild=s; /* 被插结点*s为左孩子 */
		else
			p->rchild=s; /* 被插结点*s为右孩子 */
		return TRUE;
   } else
		return FALSE; /* 树中已有关键字相同的结点，不再插入 */
}


/* 从二叉排序树中删除结点p，并重接它的左或右子树*/
void Delete(BiTree *p)
{
	BiTree q,s;
	if(!(*p)->rchild) /* 右子树空则只需重接它的左子树（待删结点是叶子也走此分支） */
	{
		q=*p;
		*p=(*p)->lchild;
		free(q);
	}else if(!(*p)->lchild) /* 只需重接它的右子树 */
	{
		q=*p;
		*p=(*p)->rchild;
		free(q);
	}else /* 左右子树均不空 */
	{
		q=*p;
		s=(*p)->lchild;
		while(s->rchild) /* 转左，然后向右到尽头（找待删结点的前驱） */
		{
			q=s;
			s=s->rchild;
		}
		(*p)->data=s->data; /* s指向被删结点的＂前驱＂（将被删结点前驱的值取代被删结点的值） */
		if(q!=*p)
		q->rchild=s->lchild; /* 重接*q的右子树 */
		else
		q->lchild=s->lchild; /* 重接*q的左子树 */
		free(s);
   }

}


/* 
* 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点
* 并返回TRUE；否则返回FALSE 
*/
Status DeleteBST(BiTree *T,ElemType key)
{ 
	if(!*T) /* 不存在关键字等于key的数据元素 */
		return FALSE;
	else
	{
		if(key==(*T)->data) /* 找到关键字等于key的数据元素 */
			Delete(T);
		else if(key<(*T)->data)
			DeleteBST(&(*T)->lchild,key);
		else
			DeleteBST(&(*T)->rchild,key);
		return TRUE;
	}
}

/* 
* 初始条件: 动态查找表DT存在，Visit是对结点操作的应用函数 *
* 操作结果: 按关键字的顺序对DT的每个结点调用函数Visit()一次且至多一次 
*/
void TraverseDSTable(BiTree DT)
{ 
	if(DT)
	{
		TraverseDSTable(DT->lchild); /* 先中序遍历左子树 */
		printf("%d ",DT->data);
		TraverseDSTable(DT->rchild); /* 最后中序遍历右子树 */
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
* 当二叉排序树T中不存在关键字等于key的数据元素时，插入e并返回1
* 否则返回0
*/
int InsertBST_1(BiTree *T, ElemType e)
{ 
	BiTNode *p,*f,*s;
	f=NULL;	/* f记录上次比较的节点指针 */
	p=*T;  /* p的初值指向根结点 */
	while(p){
		if(p->data==e) /* 树中已有key，无须插入*/
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
* 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点
* 并返回1；否则返回0
*/
int DeleteBST_1(BiTree *T,ElemType e)
{
	BiTNode *p,*q,*f,*s;
	if(*T==NULL)
		return 0;
	f=NULL;//记录上次查找节点指针
	p=(*T);//当前查找节点指针
	while(p){
		if(p->data==e)
			break;
		f=p;
		if(e<p->data)
			p=p->lchild;
		else
			p=p->rchild;
	}
	if(p==NULL)//查找完毕没找到不需要删除立即返回
		return 0;
	//找到了分三种情况
	if(p->lchild==NULL){
		if(f==NULL){
			*T=p->rchild;
		}else{		//直接把右子树接到父节点
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
		}else{	////直接把左子树接到父节点
			if(f->lchild==p)
				f->lchild==p->lchild;
			else
				f->rchild=p->lchild;
		}
		free(p);
	}else{
		q=p;
		s=p->lchild;//找左子树的最右下节点s作为代替的删除节点，q为s父节点(q有可能就是p)
		while(s->rchild){
			q=s;
			s=s->rchild;
		}
		p->data=s->data;//s为被删除节点前驱
		if(q!=p)//重接s左子树
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