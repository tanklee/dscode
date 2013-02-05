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

typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef BiTree ElemType;
#define MAX 100


/************************************ SqStack ***********************************************************/
#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

typedef struct{
	ElemType *base;
	ElemType *top;
	int stacksize;
}SqStack;

Status InitStack(SqStack *S)
{
	(*S).base=(ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));
	if(!(*S).base)
		exit(OVERFLOW);
	(*S).top=(*S).base;
	(*S).stacksize=STACK_INIT_SIZE;
	return OK;
}

Status DestroyStack(SqStack *S)
{
	free((*S).base);
	(*S).base=NULL;
	(*S).top=NULL;
	(*S).stacksize=0;
	return OK;
}

Status ClearStack(SqStack *S)
{
	(*S).top=(*S).base;
	return OK;
}

Status StackEmpty(SqStack S)
{
	if(S.top==S.base)
		return TRUE;
	else
		return FALSE;
}

int StackLength(SqStack S)
{
	return S.top-S.base;
}

Status GetTop(SqStack S,ElemType *e)
{
	if(S.top==S.base)
		return ERROR;
	*e=*(S.top-1);
	return OK;
}

Status Push(SqStack *S,ElemType e)
{
	if(((*S).top-(*S).base) >= (*S).stacksize)
	{
		(*S).base=(ElemType *)realloc((*S).base,((*S).stacksize+STACK_INCREMENT)*sizeof(ElemType));
		if(!(*S).base)
			exit(OVERFLOW);
		(*S).top=(*S).base+(*S).stacksize;
		(*S).stacksize+=STACK_INCREMENT;
	}
	*((*S).top++)=e;
	return OK;
}

Status Pop(SqStack *S,ElemType *e)
{
	if((*S).top == (*S).base)
		return ERROR;
	*e=*(--(*S).top);
	return OK;
}
/************************************ SqStack ***********************************************************/


/************************************ SqQueue ***********************************************************/
#define MAXQSIZE 100
typedef struct
{
	ElemType *base;
	int front;
	int rear;
}SqQueue;

Status InitQueue(SqQueue *Q)
{
	(*Q).base=(ElemType *)malloc(MAXQSIZE*sizeof(ElemType));
	if(!(*Q).base)
		exit(OVERFLOW);
	(*Q).front=(*Q).rear=0;
	return OK;
}

Status DestroyQueue(SqQueue *Q)
{
	if((*Q).base)
		free((*Q).base);
	(*Q).base=NULL;
	(*Q).front=(*Q).rear=0;
	return OK;
}

Status ClearQueue(SqQueue *Q)
{
	(*Q).rear=(*Q).front=0;
	return OK;
}

int QueueLength(SqQueue Q)
{
	return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
}

Status QueueEmpty(SqQueue Q)
{
	if(Q.rear==Q.front)
		return TRUE;
	else
		return FALSE;
}

Status EnQueue(SqQueue *Q,ElemType e)
{
	if(((*Q).rear+1)%MAXQSIZE==(*Q).front)
		return ERROR;
	(*Q).base[(*Q).rear]=e;
	(*Q).rear=((*Q).rear+1)%MAXQSIZE;
	return OK;
}

Status DeQueue(SqQueue *Q,ElemType *e)
{
	if((*Q).rear==(*Q).front)
		return ERROR;
	*e=(*Q).base[(*Q).front];
	(*Q).front=((*Q).front+1)%MAXQSIZE;
	return OK;
}

void QueueTraverse(SqQueue Q)
{
	int i=Q.front;
	while(i!=Q.rear)
	{
		printf("%d ",Q.base[i]);
		i=(i+1)%MAXQSIZE;
	}
	printf("\n");
}
/************************************ SqQueue ***********************************************************/


Status InitBiTree(BiTree *T)
{
	*T=NULL;
	return OK;
}

Status DestroyBiTree(BiTree *T)
{
	if(*T)
	{
		if((*T)->lchild)
			DestroyBiTree(&(*T)->lchild);
		if((*T)->rchild)
			DestroyBiTree(&(*T)->rchild);
		free(*T);
		*T=NULL;
	}
	return OK;
}

#define ClearBiTree DestroyBiTree

/* 	
* 按先序次序输入二叉树中结点的值，空格字符表示空
* 构造二叉链表表示的二叉树T						
*/
Status CreateBiTree(BiTree *T)
{
	char ch;
   	scanf("%c",&ch);
	if(ch==' ')
		*T=NULL;
	else
	{
		*T=(BiTNode *)malloc(sizeof(BiTNode));
		if(!*T)
			exit(OVERFLOW);
		(*T)->data=ch;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
	return OK;
}

Status BiTreeEmpty(BiTree T)
{
	if(T)
		return FALSE;
	else
		return TRUE;
}

/* 以广义表显示二叉树 */
void DisBiTree(BiTree T)
{
	if(T)
	{
		printf("%c",T->data);
		if((T->lchild) || (T->rchild))
		{
			printf("(");
			if(T->lchild){		
				DisBiTree(T->lchild);
			}
			if(T->rchild){
				if(T->lchild!=NULL)
					printf(",");
				DisBiTree(T->rchild);
			}
			printf(")");
		}
	}
	printf("\n");
}


/* 先序遍历递归算法 */
void PreOrderTraverse(BiTree T)
{
	 if(T)
	 {
		 printf("%c ",T->data);
		 PreOrderTraverse(T->lchild);
		 PreOrderTraverse(T->rchild);
	 }
}

/* 中序遍历递归算法 */
void InOrderTraverse(BiTree T)
{
	if(T)
	{
		InOrderTraverse(T->lchild);
		printf("%c ",T->data);
		InOrderTraverse(T->rchild);
	}
}

/* 后序遍历递归算法 */
void PostOrderTraverse(BiTree T)
{
	if(T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c ",T->data);
	}
}

/* 先序遍历非递归算法 */
void PreOrderTraverse1(BiTree T)
{
	SqStack S;
	BiTree p;
	InitStack(&S);
	p=T;
	while(p || !StackEmpty(S))
	{
		if(p)
		{
			printf("%c ",p->data);
			Push(&S,p);
			p=p->lchild;
		}
		else
		{
			Pop(&S,&p);
			p=p->rchild;
		}
	}
	printf("\n");
	DestroyStack(&S);
}

/* 先序遍历非递归算法（直接用数组实现栈）*/
void PreOrderTraverse2(BiTree T)
{
	BiTree stack[MAX],p;
	int top=0;
	p=T;
	while(p || top!=0)
	{
		if(p)
		{
			printf("%c ",p->data);
			stack[++top]=p;
			p=p->lchild;
		}
		else
		{
			p=stack[top--];
			p=p->rchild;
		}
	}
	printf("\n");
}

/* 中序遍历非递归算法 */
void InOrderTraverse1(BiTree T)
{
	SqStack S;
	BiTree p;
	InitStack(&S);
	p=T;
	while(p||!StackEmpty(S))
	{
		if(p)
		{
			Push(&S,p);
			p=p->lchild;
		}
		else
		{
			Pop(&S,&p);
			printf("%c ",p->data);
			p=p->rchild;
		}
	}
	printf("\n");
	DestroyStack(&S);
}

/* 中序遍历非递归算法（直接用数组实现栈）*/
void InOrderTraverse2(BiTree T)
{
	BiTree stack[MAX];
	BiTree p;
	int top=0;
	p=T;
	while(p || top!=0)
	{
		if(p)
		{
			stack[++top]=p;
			p=p->lchild;
		}
		else
		{
			p=stack[top--];
			printf("%c ",p->data);
			p=p->rchild;
		}
	}
	printf("\n");
}

/* 后序遍历非递归算法*/
void PostOrderTraverse1(BiTree T)
{
	SqStack S;
	BiTree p,q;
	InitStack(&S);
	p=T;
	q=NULL;
	while(p||!StackEmpty(S))
	{
		if(p)
		{
			Push(&S,p);
			p=p->lchild;
		}
		else
		{
			GetTop(S,&p);
			if(p->rchild && p->rchild!=q)
				p=p->rchild;
			else
			{
				Pop(&S,&p);
				printf("%c ",p->data);
				q=p;
				p=NULL;
			}
		}
	}
	printf("\n");
	DestroyStack(&S);
}

/* 后序遍历非递归算法（直接用数组实现栈）*/
void PostOrderTraverse2(BiTree T)
{
	BiTree stack[MAX],p,q;
	int top=0;
	p=T;
	q=NULL;
	while(p || top!=0)
	{
		if(p)
		{
			stack[++top]=p;
			p=p->lchild;
		}
		else
		{
			p=stack[top];
			if(p->rchild && p->rchild!=q)
				p=p->rchild;
			else
			{
				p=stack[top--];
				printf("%c ",p->data);
				q=p;
				p=NULL;
			}
		}
	}
	printf("\n");
}

/* 	层次遍历算法*/
void LevelOrderTraverse(BiTree T)
{
	SqQueue Q;
	BiTree p;
	InitQueue(&Q);
	if(T)
		EnQueue(&Q,T);
	while(!QueueEmpty(Q))
	{
		DeQueue(&Q,&p);
		printf("%c ",p->data);
		if(p->lchild)
			EnQueue(&Q,p->lchild);
		if(p->rchild)
			EnQueue(&Q,p->rchild);
	}
	printf("\n");
	DestroyQueue(&Q);
}


/* 层次遍历算法（直接用数组实现队列) */
void LevelOrderTraverse1(BiTree T)
{
	BiTree queue[MAX],p;
    int front,rear;
	front=rear=0;
	if(T)
		queue[rear++]=T;
	while(rear!=front)
	{
		p=queue[front++];
		printf("%c ",p->data);
		if(p->lchild)
			queue[rear++]=p->lchild;
		if(p->rchild)
			queue[rear++]=p->rchild;
	}
	printf("\n");
}


/*
* Node(T)=0 (T==NULL)
* Node(T)=1+Node(T->lchild)+Node(T->rchild);
*/
int CountNode(BiTree T)
{
	if(T==NULL)
		return 0;
	else
		return (CountNode(T->lchild)+CountNode(T->rchild)+1);
}

int CountNode1(BiTree T)
{
	SqStack S;
	BiTree p=T;
	int count=0;
	InitStack(&S);

	Push(&S,p);
	while(!StackEmpty(S))
	{
		Pop(&S,&p);
		count++;
		if(p->lchild)
			Push(&S,p->lchild);
		if(p->rchild)
			Push(&S,p->rchild);
	}
	DestroyStack(&S);
	return count;
}

/*
* Leaf(T)=0 (T=NULL)
* Leaf(T)=1 (T->lchild=NULL && T->rchild==NULL)
* Leaf(T)=Leaf(T->lchid)+Leaf(T->lchild)
*/
int CountLeaf(BiTree T)
{
	if(T==NULL)
		return 0;
	if(T->lchild==NULL && T->rchild==NULL)
		return 1;
	return CountLeaf(T->lchild) + CountLeaf(T->rchild);
}


/*
* 求二叉树深度递归算法
* Depth(T)=0 (T=NULL)
* Depth(T)=1+MAX{Depth(T->lchild),Depth(T->rchild)}
*/
int Depth(BiTree T)
{
	int ldepth,rdepth,depth;
	if(T==NULL)
		return 0;
	else
	{
		ldepth=Depth(T->lchild);
		rdepth=Depth(T->rchild);
		depth=((ldepth>=rdepth)?ldepth:rdepth)+1;	
	}
	return depth;
}


/*
* 求二叉树深度非递归算法
* 层次遍历记录层号，需要O(n)辅助空间
*/
int Depth1(BiTree T)
{
	BiTree p,queue[MAX];
	int level[MAX];
	int rear,front;
	int cur_level,max_level = 0 ;
	rear = front = 0;
	
	if(T){
	queue[rear]=T;
	level[rear] = 1;
	rear++;
	}
	while(rear != front)
	{
		p = queue[front];
		cur_level = level[front];
		front++;
		if(cur_level > max_level)
			max_level = cur_level;
		if(p->lchild){
			queue[rear] = p->lchild;
			level[rear] = cur_level+1;
			rear++;
		}
		if(p->rchild){
			queue[rear] = p->rchild;
			level[rear] = cur_level+1;
			rear++;
		}
	}
	
	return max_level;
}

/*
* 求二叉树所有叶结点的最大枝长
* maxlength(T)=0 (T==NULL)
* maxlength(T)=0 (T->lchild=NULL && T->rchild=NULL)
* maxlength(T)=1+maxlength(T->rchild) (T->lchild=NULL)
* maxlength(T)=1+maxlength(T->lchild) (T->rchild=NULL)
* maxlength(T)=1+MAX{maxlength(T->lchild),maxlength(T->rchlld)}
*/
int maxlength(BiTree T)
{
	int len,llen,rlen;
	if(T==NULL)
		return 0;
	else if(T->lchild==NULL && T->rchild==NULL)
		return 0;
	else if(T->lchild==NULL)
		return (1+maxlength(T->rchild));
	else if(T->rchild==NULL)
		return (1+maxlength(T->lchild));
	else
	{
		llen=maxlength(T->lchild);
		rlen=maxlength(T->rchild);
		len=((llen>=rlen)?llen:rlen)+1;
		return len;
	}
}




int main()
{
	BiTree T;
	InitBiTree(&T);
	
	
	CreateBiTree(&T);

/*
	printf("preorder:\n");
	PreOrderTraverse(T);
	printf("\n");

	printf("inorder:\n");
	InOrderTraverse(T);
	printf("\n");

	printf("postorder:\n");
	PostOrderTraverse(T);
	printf("\n");

	
	printf("preorder1:\n");
	PreOrderTraverse1(T);

	printf("inorder1:\n");
	InOrderTraverse1(T);

	printf("postorder1:\n");
	PostOrderTraverse1(T);

	printf("preorder2:\n");
	PreOrderTraverse2(T);

	printf("inorder2:\n");
	InOrderTraverse2(T);

	printf("postorder2:\n");
	PostOrderTraverse2(T);

	printf("levelorder:\n");
	LevelOrderTraverse(T);

	printf("levelorder1:\n");
	LevelOrderTraverse1(T);*/

    DisBiTree(T);
	printf("countnode=%d\n",CountNode(T));
	printf("countnode1=%d\n",CountNode1(T));

	printf("leafnode=%d\n",CountLeaf(T));

	printf("depth=%d\n",Depth(T));
	printf("depth1=%d\n",Depth1(T));

	printf("maxlength=%d\n",maxlength(T));

	DestroyBiTree(&T);
 	return 0;
}
/*
input example:
abc  de g  f   ###
*/