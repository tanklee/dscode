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


/*图的数组(邻接矩阵)存储表示 */
#define INFINITY INT_MAX /* 用整型最大值代替∞ */
#define MAX_VERTEX_NUM 20 /* 最大顶点个数 */

#define MAX_NAME 5
#define MAX_INFO 20
typedef int VRType;
typedef char InfoType;
typedef char VertexType[MAX_NAME];

typedef enum{DG,DN,AG,AN}GraphKind; /* {有向图,有向网,无向图,无向网} */
typedef struct
{
	VRType adj; /* 顶点关系类型。对无权图，用1(是)或0(否)表示相邻否； */
	            /* 对带权图，c则为权值类型 */
	InfoType *info; /* 该弧相关信息的指针(可无) */
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{
   VertexType vexs[MAX_VERTEX_NUM]; /* 顶点向量 */
   AdjMatrix arcs; /* 邻接矩阵 */
   int vexnum,arcnum; /* 图的当前顶点数和弧数 */
   GraphKind kind; /* 图的种类标志 */
}MGraph;


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
* 初始条件:图G存在,u和G中顶点有相同特征 
* 操作结果:若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 
*/
int LocateVex(MGraph G,VertexType u)
{
	int i;
	for(i=0;i<G.vexnum;i++)
		if(strcmp(u,G.vexs[i])==0)
			return i;
	return -1;
}


/* 采用数组(邻接矩阵)表示法,构造有向图G */
Status CreateDG(MGraph *G)
{ 
	int i,j,k,l,IncInfo;
	char s[MAX_INFO],*info;
	VertexType va,vb;

	printf("请输入有向图G的顶点数,弧数,弧是否含其它信息(是:1,否:0): ");
	scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);

	printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
	for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
		scanf("%s",(*G).vexs[i]);
	for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
		for(j=0;j<(*G).vexnum;++j)
		{
			(*G).arcs[i][j].adj=0; /* 图 */
			(*G).arcs[i][j].info=NULL;
		}

	printf("请输入%d条弧的弧尾 弧头(以空格作为间隔): \n",(*G).arcnum);
	for(k=0;k<(*G).arcnum;++k)
	{
		scanf("%s%s%*c",va,vb);  /* %*c吃掉回车符 */
		i=LocateVex(*G,va);
		j=LocateVex(*G,vb);
		(*G).arcs[i][j].adj=1; /* 有向图 */
		if(IncInfo)
		{
			printf("请输入该弧的相关信息(<%d个字符): ",MAX_INFO);
			gets(s);
			l=strlen(s);
			if(l)
			{
				info=(char*)malloc((l+1)*sizeof(char));
				strcpy(info,s);
				(*G).arcs[i][j].info=info; /* 有向 */
			}
		}
   }

   (*G).kind=DG;
   return OK;
}


/* 采用数组(邻接矩阵)表示法,构造有向网G */
Status CreateDN(MGraph *G)
{ 
	int i,j,k,w,IncInfo;
	char s[MAX_INFO],*info;
	VertexType va,vb;

	printf("请输入有向网G的顶点数,弧数,弧是否含其它信息(是:1,否:0): ");
	scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);

	printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
	for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
		scanf("%s",(*G).vexs[i]);
	for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
		for(j=0;j<(*G).vexnum;++j)
		{
			(*G).arcs[i][j].adj=INFINITY; /* 网 */
			(*G).arcs[i][j].info=NULL;
		}

	printf("请输入%d条弧的弧尾 弧头 权值(以空格作为间隔): \n",(*G).arcnum);
	for(k=0;k<(*G).arcnum;++k)
	{
		scanf("%s%s%d%*c",va,vb,&w);  /* %*c吃掉回车符 */
		i=LocateVex(*G,va);
		j=LocateVex(*G,vb);
		(*G).arcs[i][j].adj=w; /* 有向网 */
		if(IncInfo)
		{
			printf("请输入该弧的相关信息(<%d个字符): ",MAX_INFO);
			gets(s);
			w=strlen(s);
			if(w)
			{
				info=(char*)malloc((w+1)*sizeof(char));
				strcpy(info,s);
				(*G).arcs[i][j].info=info; /* 有向 */
			}
		}
	}

   (*G).kind=DN;
   return OK;
}


/* 采用数组(邻接矩阵)表示法,构造无向图G */
Status CreateAG(MGraph *G)
{
	int i,j,k,l,IncInfo;
	char s[MAX_INFO],*info;
	VertexType va,vb;
	printf("请输入无向图G的顶点数,边数,边是否含其它信息(是:1,否:0): ");
	scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
	
	printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
	for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
		scanf("%s",(*G).vexs[i]);
	for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
		for(j=0;j<(*G).vexnum;++j)
		{
			(*G).arcs[i][j].adj=0; /* 图 */
			(*G).arcs[i][j].info=NULL;
		}

   printf("请输入%d条边的顶点1 顶点2(以空格作为间隔): \n",(*G).arcnum);
   for(k=0;k<(*G).arcnum;++k)
   {
		scanf("%s%s%*c",va,vb); /* %*c吃掉回车符 */
		i=LocateVex(*G,va);
		j=LocateVex(*G,vb);
		(*G).arcs[i][j].adj=(*G).arcs[j][i].adj=1; /* 无向图 */
		if(IncInfo)
		{
			printf("请输入该边的相关信息(<%d个字符): ",MAX_INFO);
			gets(s);
			l=strlen(s);
			if(l)
			{
				info=(char*)malloc((l+1)*sizeof(char));
				strcpy(info,s);
				(*G).arcs[i][j].info=(*G).arcs[j][i].info=info; /* 无向 */
			}
		}
   }

   (*G).kind=AG;
   return OK;
}


/* 采用数组(邻接矩阵)表示法,构造无向网G。算法7.2 */
Status CreateAN(MGraph *G)
{ 
	int i,j,k,w,IncInfo;
	char s[MAX_INFO],*info;
	VertexType va,vb;

	printf("请输入无向网G的顶点数,边数,边是否含其它信息(是:1,否:0): ");
	scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);

	printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
	for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
		scanf("%s",(*G).vexs[i]);
	for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
		for(j=0;j<(*G).vexnum;++j)
		{
			(*G).arcs[i][j].adj=INFINITY; /* 网 */
			(*G).arcs[i][j].info=NULL;
		}

	printf("请输入%d条边的顶点1 顶点2 权值(以空格作为间隔): \n",(*G).arcnum);
	for(k=0;k<(*G).arcnum;++k)
	{
		scanf("%s%s%d%*c",va,vb,&w); /* %*c吃掉回车符 */
		i=LocateVex(*G,va);
		j=LocateVex(*G,vb);
		(*G).arcs[i][j].adj=(*G).arcs[j][i].adj=w; /* 无向 */
		if(IncInfo)
		{
			printf("请输入该边的相关信息(<%d个字符): ",MAX_INFO);
			gets(s);
			w=strlen(s);
			if(w)
			{
				info=(char*)malloc((w+1)*sizeof(char));
				strcpy(info,s);
				(*G).arcs[i][j].info=(*G).arcs[j][i].info=info; /* 无向 */
			}
		}
	}

	(*G).kind=AN;
	return OK;
}



/* 采用数组(邻接矩阵)表示法,构造图G。算法7.1 */
Status CreateGraph(MGraph *G)
{ 
	printf("请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3): ");
	scanf("%d",&(*G).kind);
	switch((*G).kind)
	{
		case DG: return CreateDG(G); /* 构造有向图 */
		case DN: return CreateDN(G); /* 构造有向网 */
		case AG: return CreateAG(G); /* 构造无向图 */
		case AN: return CreateAN(G); /* 构造无向网 */
		default: return ERROR;
   }
}


/* 初始条件: 图G存在。操作结果: 销毁图G */
void DestroyGraph(MGraph *G)
{ 
	int i,j;
	if((*G).kind<2) /* 有向 */
	{
		for(i=0;i<(*G).vexnum;i++) /* 释放弧的相关信息(如果有的话) */
			for(j=0;j<(*G).vexnum;j++)
				if((*G).arcs[i][j].adj==1&&(*G).kind==0||(*G).arcs[i][j].adj!=INFINITY&&(*G).kind==1) /* 有向图的弧||有向网的弧 */
				if((*G).arcs[i][j].info) /* 有相关信息 */
				{
					free((*G).arcs[i][j].info);
					(*G).arcs[i][j].info=NULL;
				}
	}

   else /* 无向 */
		for(i=0;i<(*G).vexnum;i++) /* 释放边的相关信息(如果有的话) */
			for(j=i+1;j<(*G).vexnum;j++)
				if((*G).arcs[i][j].adj==1&&(*G).kind==2||(*G).arcs[i][j].adj!=INFINITY&&(*G).kind==3) /* 无向图的边||无向网的边 */
					if((*G).arcs[i][j].info) /* 有相关信息 */
					{
						free((*G).arcs[i][j].info);
						(*G).arcs[i][j].info=(*G).arcs[j][i].info=NULL;
					}

   (*G).vexnum=0;
   (*G).arcnum=0;
}

/* 输出邻接矩阵G */
void Display(MGraph G)
{ 
	int i,j;
	char s[7],s1[3];
	switch(G.kind)
	{
		case DG: strcpy(s,"有向图\0");
				strcpy(s1,"弧\0");
				break;
		case DN: strcpy(s,"有向网\0");
				strcpy(s1,"弧\0");
				break;
		case AG: strcpy(s,"无向图\0");
				strcpy(s1,"边\0");
				break;
		case AN: strcpy(s,"无向网\0");
				strcpy(s1,"边\0");
	}

	printf("%d个顶点%d条%s的%s\n",G.vexnum,G.arcnum,s1,s);
	
	for(i=0;i<G.vexnum;++i) /* 输出G.vexs */
		printf("G.vexs[%d]=%s\n",i,G.vexs[i]);
	
	printf("G.arcs.adj:\n"); /* 输出G.arcs.adj */
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
			printf("%6d",G.arcs[i][j].adj);
		printf("\n");
	}

	printf("G.arcs.info:\n"); /* 输出G.arcs.info */
	printf("顶点1(弧尾) 顶点2(弧头) 该%s信息：\n",s1);
	if(G.kind<2) /* 有向 */
		for(i=0;i<G.vexnum;i++)
			for(j=0;j<G.vexnum;j++)
			{
				if(G.arcs[i][j].info)
					printf("%5s %11s     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
			}
   else /* 无向 */
   {
	   for(i=0;i<G.vexnum;i++)
			for(j=i+1;j<G.vexnum;j++)
				if(G.arcs[i][j].info)
					printf("%5s %11s     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
   }

}


/* 
* 初始条件: 图G存在,v是G中某个顶点 
* 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1 
*/
int FirstAdjVex(MGraph G,VertexType v)
{ 
	int i,value=0,k;
	k=LocateVex(G,v); /* k为顶点v在图G中的序号 */
	if(G.kind==DN||G.kind==AN) /* 网 */
		value=INFINITY;
	for(i=0;i<G.vexnum;i++)
		if(G.arcs[k][i].adj!=value)
			return i;
	return -1;
}


/* 
* 初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点 
* 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号, 
*           若w是v的最后一个邻接顶点,则返回-1 
*/
int NextAdjVex(MGraph G,VertexType v,VertexType w)
{ 
	int i,value=0,k1,k2;
	k1=LocateVex(G,v); /* k1为顶点v在图G中的序号 */
	k2=LocateVex(G,w); /* k2为顶点w在图G中的序号 */
	if(G.kind==DN||G.kind==AN) /* 网 */
		value=INFINITY;
	for(i=k2+1;i<G.vexnum;i++)
		if(G.arcs[k1][i].adj!=value)
			return i;
	return -1;
}

Status visit(VertexType i)
{
   printf("%s ",i);
   return OK;
}

Boolean visited[MAX_VERTEX_NUM]; /* 访问标志数组(全局量) */
Status(*VisitFunc)(VertexType); /* 函数变量 */

/* 从第v个顶点出发递归地深度优先遍历图G。算法7.5 */
void DFS(MGraph G,int v)
{ 
	int w;
	visited[v]=TRUE; /* 设置访问标志为TRUE(已访问) */
	VisitFunc(G.vexs[v]); /* 访问第v个顶点 */

	for(w=FirstAdjVex(G,G.vexs[v]);w>=0;w=NextAdjVex(G,G.vexs[v],G.vexs[w]))
		if(!visited[w])
			DFS(G,w);/* 对v的尚未访问的序号为w的邻接顶点递归调用DFS */
}


/*
* 初始条件: 图G存在,Visit是顶点的应用函数。算法7.4 
* 操作结果: 从第1个顶点起,深度优先遍历图G,并对每个顶点调用函数Visit 
*  一次且仅一次。一旦Visit()失败,则操作失败
*/
void DFSTraverse(MGraph G,Status(*Visit)(VertexType v))
{ 
	int v;
	VisitFunc=Visit; /* 使用全局变量VisitFunc,使DFS不必设函数指针参数 */
	for(v=0;v<G.vexnum;v++)
		visited[v]=FALSE; /* 访问标志数组初始化(未被访问) */
	for(v=0;v<G.vexnum;v++)
		if(!visited[v])
			DFS(G,v); /* 对尚未访问的顶点调用DFS */
	printf("\n");
}


/* 
* 初始条件: 图G存在,Visit是顶点的应用函数。算法7.6 
* 操作结果: 从第1个顶点起,按广度优先非递归遍历图G,并对每个顶点调用函数 
*           Visit一次且仅一次。一旦Visit()失败,则操作失败。 
*           使用辅助队列Q和访问标志数组visited 
*/
void BFSTraverse(MGraph G,Status(*Visit)(VertexType v))
{
	int i,j,w;
	SqQueue Q;
	
	for(i=0;i<G.vexnum;i++)
		visited[i]=FALSE; /* 置初值 */
	InitQueue(&Q); /* 置空的辅助队列Q */
	
	for(i=0;i<G.vexnum;i++)
		if(!visited[i]) /* v尚未访问 */
		{
			visited[i]=TRUE; /* 设置访问标志为TRUE(已访问) */
			Visit(G.vexs[i]);
			EnQueue(&Q,i); /* v入队列 */
			while(!QueueEmpty(Q)) /* 队列不空 */
			{
				DeQueue(&Q,&j); /* 队头元素出队并置为u */
				for(w=FirstAdjVex(G,G.vexs[j]);w>=0;w=NextAdjVex(G,G.vexs[j],G.vexs[w]))
				if(!visited[w]) /* w为u的尚未访问的邻接顶点的序号 */
				{
					visited[w]=TRUE;
					Visit(G.vexs[w]);
					EnQueue(&Q,w);
				}
			}
		}

	printf("\n");
	DestroyQueue(&Q);
}

int main()
{
	MGraph G;
	CreateGraph(&G);
	Display(G);
	DFSTraverse(G,visit);
	BFSTraverse(G,visit);
	DestroyGraph(&G);
	return 0;
}
