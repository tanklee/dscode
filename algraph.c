#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int Boolean;

FILE *fp;
/*图的数组(邻接矩阵)存储表示 */
#define INFINITY INT_MAX /* 用整型最大值代替∞ */
#define MAX_VERTEX_NUM 20 /* 最大顶点个数 */

#define MAX_NAME 5
#define MAX_INFO 20
typedef int VRType;
typedef int InfoType;
typedef char VertexType[MAX_NAME];

typedef enum{DG,DN,AG,AN}GraphKind; /* {有向图,有向网,无向图,无向网} */
typedef struct ArcNode
{
	int adjvex; /* 该弧所指向的顶点的位置 */
	struct ArcNode *nextarc; /* 指向下一条弧的指针 */
	InfoType *info; /* 网的权值指针） */
}ArcNode; /* 表结点 */

typedef struct VNode
{
	VertexType data; /* 顶点信息 */
	ArcNode *firstarc; /* 第一个表结点的地址,指向第一条依附该顶点的弧的指针 */
}VNode,AdjList[MAX_VERTEX_NUM]; /* 头结点 */

typedef struct
{
	AdjList vertices;
	int vexnum,arcnum; /* 图的当前顶点数和弧数 */
	int kind; /* 图的种类标志 */
}ALGraph;


/************************************ SqQueue ***********************************************************/
typedef int ElemType;
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


/* 
* 初始条件: 图G存在,u和G中顶点有相同特征 
* 操作结果: 若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 
*/
int LocateVex(ALGraph G,VertexType u)
{ 
   int i;
   for(i=0;i<G.vexnum;++i)
     if(strcmp(u,G.vertices[i].data)==0)
       return i;
   return -1;
}


/* 采用邻接表存储结构,构造没有相关信息的图G(用一个函数构造4种图) */
Status CreateGraph(ALGraph *G)
{ 
	int i,j,k;
	int w; /* 权值 */
    VertexType va,vb;
    ArcNode *p;

    printf("请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3): ");
    fscanf(fp,"%d",&(*G).kind);
	printf("请输入图的顶点数,边数: ");
		fscanf(fp,"%d%d",&(*G).vexnum,&(*G).arcnum);
	printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
	for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
	{
		fscanf(fp,"%s",(*G).vertices[i].data);
		(*G).vertices[i].firstarc=NULL;
	}
	
	if((*G).kind==1||(*G).kind==3) /* 网 */
		printf("请顺序输入每条弧(边)的权值、弧尾和弧头(以空格作为间隔):\n");
	else /* 图 */
		printf("请顺序输入每条弧(边)的弧尾和弧头(以空格作为间隔):\n");
	for(k=0;k<(*G).arcnum;++k) /* 构造表结点链表 */
	{
		if((*G).kind==1||(*G).kind==3) /* 网 */
			fscanf(fp,"%d%s%s",&w,va,vb);
		else /* 图 */
			fscanf(fp,"%s%s",va,vb);
		
		i=LocateVex(*G,va); /* 弧尾 */
		j=LocateVex(*G,vb); /* 弧头 */
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=j;
		if((*G).kind==1||(*G).kind==3) /* 网 */
		{
			p->info=(int *)malloc(sizeof(int));
			*(p->info)=w;
		}
		else
			p->info=NULL; /* 图 */
		
		p->nextarc=(*G).vertices[i].firstarc; /* 插在表头 */
		(*G).vertices[i].firstarc=p;
		
		if((*G).kind>=2) /* 无向图或网,产生第二个表结点 */
		{
			p=(ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex=i;
			if((*G).kind==3) /* 无向网 */
			{
				p->info=(int*)malloc(sizeof(int));
				*(p->info)=w;
			}
			else
				p->info=NULL; /* 无向图 */
			p->nextarc=(*G).vertices[j].firstarc; /* 插在表头 */
			(*G).vertices[j].firstarc=p;
		}
	}
	return OK;
}


/* 初始条件: 图G存在。操作结果: 销毁图G */
void DestroyGraph(ALGraph *G)
{ 
	int i;
	ArcNode *p,*q;
	(*G).vexnum=0;
	(*G).arcnum=0;
	for(i=0;i<(*G).vexnum;++i)
	{
		p=(*G).vertices[i].firstarc;
		while(p)
		{
			q=p->nextarc;
			if((*G).kind%2) /* 网 */
				free(p->info);
			free(p);
			p=q;
		}
   }
}

/*
* 初始条件: 图G存在,v是G中某个顶点 
* 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1 
*/
int FirstAdjVex(ALGraph G,VertexType v)
{ 
	ArcNode *p;
    int v1;
    v1=LocateVex(G,v); /* v1为顶点v在图G中的序号 */
    p=G.vertices[v1].firstarc;
    if(p)
	    return p->adjvex;
    else
	    return -1;
}

/* 
* 初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点 
* 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号。 
*           若w是v的最后一个邻接点,则返回-1 
*/
int NextAdjVex(ALGraph G,VertexType v,VertexType w)
{ 
	ArcNode *p;
	int v1,w1;
	v1=LocateVex(G,v); /* v1为顶点v在图G中的序号 */
	w1=LocateVex(G,w); /* w1为顶点w在图G中的序号 */
	p=G.vertices[v1].firstarc;
	while(p&&p->adjvex!=w1) /* 指针p不空且所指表结点不是w */
		p=p->nextarc;
	if(!p||!p->nextarc) /* 没找到w或w是最后一个邻接点 */
		return -1;
	else /* p->adjvex==w */
		return p->nextarc->adjvex; /* 返回v的(相对于w的)下一个邻接顶点的序号 */
}


/* 输出图的邻接矩阵G */
void Display(ALGraph G)
{
	int i;
	ArcNode *p;
	switch(G.kind)
	{
		case DG: printf("有向图\n");
			break;
		case DN: printf("有向网\n");
            break;
		case AG: printf("无向图\n");
            break;
		case AN: printf("无向网\n");
	}
	printf("%d个顶点：\n",G.vexnum);
	for(i=0;i<G.vexnum;++i)
		printf("%s ",G.vertices[i].data);
	
	printf("\n%d条弧(边):\n",G.arcnum);
	for(i=0;i<G.vexnum;i++)
	{
		p=G.vertices[i].firstarc;
		while(p)
		{
			if(G.kind<=1) /* 有向 */
			{
				printf("%s→%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
				if(G.kind==DN) /* 网 */
				printf(":%d ",*(p->info));
			}
			else /* 无向(避免输出两次) */
			{
				if(i<p->adjvex)
				{
					printf("%s－%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
					if(G.kind==AN) /* 网 */
						printf(":%d ",*(p->info));
				}
			}
			p=p->nextarc;
		}
		printf("\n");
	}

}

Status visit(VertexType i)
{
   printf("%s ",i);
   return OK;
}

Boolean visited[MAX_VERTEX_NUM]; /* 访问标志数组(全局量) */
Status (*VisitFunc)(VertexType v); /* 函数变量(全局量) */

/* 从第v个顶点出发递归地深度优先遍历图G。算法7.5 */
void DFS(ALGraph G,int v)
{ 
	int w;	
	visited[v]=TRUE; /* 设置访问标志为TRUE(已访问) */
	VisitFunc(G.vertices[v].data); /* 访问第v个顶点 */
	for(w=FirstAdjVex(G,G.vertices[v].data);w>=0;w=NextAdjVex(G,G.vertices[v].data,G.vertices[w].data))
		if(!visited[w])
			DFS(G,w); /* 对v的尚未访问的邻接点w递归调用DFS */
}

/* 对图G作深度优先遍历。算法7.4 */
void DFSTraverse(ALGraph G,Status (*Visit)(VertexType v))
{
	int i;
	VisitFunc=Visit; /* 使用全局变量VisitFunc,使DFS不必设函数指针参数 */
	for(i=0;i<G.vexnum;i++)
		visited[i]=FALSE; /* 访问标志数组初始化 */
	for(i=0;i<G.vexnum;i++)
		if(!visited[i])
			DFS(G,i); /* 对尚未访问的顶点调用DFS */
	printf("\n");
}

/*按广度优先非递归遍历图G。使用辅助队列Q和访问标志数组visited。算法7.6 */
void BFSTraverse(ALGraph G,Status (*Visit)(VertexType v))
{
	int i,j,w;
	SqQueue Q;
	
	for(i=0;i<G.vexnum;i++)
		visited[i]=FALSE; /* 置初值 */
	InitQueue(&Q); /* 置空的辅助队列Q */
	for(i=0;i<G.vexnum;i++) /* 如果是连通图,只v=0就遍历全图 */
		if(!visited[i]) /* v尚未访问 */
		{
			visited[i]=TRUE;
			Visit(G.vertices[i].data);
			EnQueue(&Q,i); /* v入队列 */
			while(!QueueEmpty(Q)) /* 队列不空 */
			{
				DeQueue(&Q,&j); /* 队头元素出队并置为u */
				for(w=FirstAdjVex(G,G.vertices[j].data);w>=0;w=NextAdjVex(G,G.vertices[j].data,G.vertices[w].data))
					if(!visited[w]) /* w为u的尚未访问的邻接顶点 */
					{
						visited[w]=TRUE;
						Visit(G.vertices[w].data);
						EnQueue(&Q,w); /* w入队 */
					}
			}
		}

	printf("\n");
}
int main()
{
	ALGraph G;
	CreateGraph(&G);
	fp=fopen("graph.txt","r");
	if(fp==NULL){
		printf("open file error\n");
		exit(1);
	}
	Display(G);
	DFSTraverse(G,visit);
	BFSTraverse(G,visit);
	DestroyGraph(&G);
	return 0;
}