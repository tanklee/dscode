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
/*ͼ������(�ڽӾ���)�洢��ʾ */
#define INFINITY INT_MAX /* ���������ֵ����� */
#define MAX_VERTEX_NUM 20 /* ��󶥵���� */

#define MAX_NAME 5
#define MAX_INFO 20
typedef int VRType;
typedef int InfoType;
typedef char VertexType[MAX_NAME];

typedef enum{DG,DN,AG,AN}GraphKind; /* {����ͼ,������,����ͼ,������} */
typedef struct ArcNode
{
	int adjvex; /* �û���ָ��Ķ����λ�� */
	struct ArcNode *nextarc; /* ָ����һ������ָ�� */
	InfoType *info; /* ����Ȩֵָ�룩 */
}ArcNode; /* ���� */

typedef struct VNode
{
	VertexType data; /* ������Ϣ */
	ArcNode *firstarc; /* ��һ������ĵ�ַ,ָ���һ�������ö���Ļ���ָ�� */
}VNode,AdjList[MAX_VERTEX_NUM]; /* ͷ��� */

typedef struct
{
	AdjList vertices;
	int vexnum,arcnum; /* ͼ�ĵ�ǰ�������ͻ��� */
	int kind; /* ͼ�������־ */
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
* ��ʼ����: ͼG����,u��G�ж�������ͬ���� 
* �������: ��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1 
*/
int LocateVex(ALGraph G,VertexType u)
{ 
   int i;
   for(i=0;i<G.vexnum;++i)
     if(strcmp(u,G.vertices[i].data)==0)
       return i;
   return -1;
}


/* �����ڽӱ�洢�ṹ,����û�������Ϣ��ͼG(��һ����������4��ͼ) */
Status CreateGraph(ALGraph *G)
{ 
	int i,j,k;
	int w; /* Ȩֵ */
    VertexType va,vb;
    ArcNode *p;

    printf("������ͼ������(����ͼ:0,������:1,����ͼ:2,������:3): ");
    fscanf(fp,"%d",&(*G).kind);
	printf("������ͼ�Ķ�����,����: ");
		fscanf(fp,"%d%d",&(*G).vexnum,&(*G).arcnum);
	printf("������%d�������ֵ(<%d���ַ�):\n",(*G).vexnum,MAX_NAME);
	for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
	{
		fscanf(fp,"%s",(*G).vertices[i].data);
		(*G).vertices[i].firstarc=NULL;
	}
	
	if((*G).kind==1||(*G).kind==3) /* �� */
		printf("��˳������ÿ����(��)��Ȩֵ����β�ͻ�ͷ(�Կո���Ϊ���):\n");
	else /* ͼ */
		printf("��˳������ÿ����(��)�Ļ�β�ͻ�ͷ(�Կո���Ϊ���):\n");
	for(k=0;k<(*G).arcnum;++k) /* ����������� */
	{
		if((*G).kind==1||(*G).kind==3) /* �� */
			fscanf(fp,"%d%s%s",&w,va,vb);
		else /* ͼ */
			fscanf(fp,"%s%s",va,vb);
		
		i=LocateVex(*G,va); /* ��β */
		j=LocateVex(*G,vb); /* ��ͷ */
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=j;
		if((*G).kind==1||(*G).kind==3) /* �� */
		{
			p->info=(int *)malloc(sizeof(int));
			*(p->info)=w;
		}
		else
			p->info=NULL; /* ͼ */
		
		p->nextarc=(*G).vertices[i].firstarc; /* ���ڱ�ͷ */
		(*G).vertices[i].firstarc=p;
		
		if((*G).kind>=2) /* ����ͼ����,�����ڶ������� */
		{
			p=(ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex=i;
			if((*G).kind==3) /* ������ */
			{
				p->info=(int*)malloc(sizeof(int));
				*(p->info)=w;
			}
			else
				p->info=NULL; /* ����ͼ */
			p->nextarc=(*G).vertices[j].firstarc; /* ���ڱ�ͷ */
			(*G).vertices[j].firstarc=p;
		}
	}
	return OK;
}


/* ��ʼ����: ͼG���ڡ��������: ����ͼG */
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
			if((*G).kind%2) /* �� */
				free(p->info);
			free(p);
			p=q;
		}
   }
}

/*
* ��ʼ����: ͼG����,v��G��ĳ������ 
* �������: ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ���,�򷵻�-1 
*/
int FirstAdjVex(ALGraph G,VertexType v)
{ 
	ArcNode *p;
    int v1;
    v1=LocateVex(G,v); /* v1Ϊ����v��ͼG�е���� */
    p=G.vertices[v1].firstarc;
    if(p)
	    return p->adjvex;
    else
	    return -1;
}

/* 
* ��ʼ����: ͼG����,v��G��ĳ������,w��v���ڽӶ��� 
* �������: ����v��(�����w��)��һ���ڽӶ������š� 
*           ��w��v�����һ���ڽӵ�,�򷵻�-1 
*/
int NextAdjVex(ALGraph G,VertexType v,VertexType w)
{ 
	ArcNode *p;
	int v1,w1;
	v1=LocateVex(G,v); /* v1Ϊ����v��ͼG�е���� */
	w1=LocateVex(G,w); /* w1Ϊ����w��ͼG�е���� */
	p=G.vertices[v1].firstarc;
	while(p&&p->adjvex!=w1) /* ָ��p��������ָ���㲻��w */
		p=p->nextarc;
	if(!p||!p->nextarc) /* û�ҵ�w��w�����һ���ڽӵ� */
		return -1;
	else /* p->adjvex==w */
		return p->nextarc->adjvex; /* ����v��(�����w��)��һ���ڽӶ������� */
}


/* ���ͼ���ڽӾ���G */
void Display(ALGraph G)
{
	int i;
	ArcNode *p;
	switch(G.kind)
	{
		case DG: printf("����ͼ\n");
			break;
		case DN: printf("������\n");
            break;
		case AG: printf("����ͼ\n");
            break;
		case AN: printf("������\n");
	}
	printf("%d�����㣺\n",G.vexnum);
	for(i=0;i<G.vexnum;++i)
		printf("%s ",G.vertices[i].data);
	
	printf("\n%d����(��):\n",G.arcnum);
	for(i=0;i<G.vexnum;i++)
	{
		p=G.vertices[i].firstarc;
		while(p)
		{
			if(G.kind<=1) /* ���� */
			{
				printf("%s��%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
				if(G.kind==DN) /* �� */
				printf(":%d ",*(p->info));
			}
			else /* ����(�����������) */
			{
				if(i<p->adjvex)
				{
					printf("%s��%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
					if(G.kind==AN) /* �� */
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

Boolean visited[MAX_VERTEX_NUM]; /* ���ʱ�־����(ȫ����) */
Status (*VisitFunc)(VertexType v); /* ��������(ȫ����) */

/* �ӵ�v����������ݹ��������ȱ���ͼG���㷨7.5 */
void DFS(ALGraph G,int v)
{ 
	int w;	
	visited[v]=TRUE; /* ���÷��ʱ�־ΪTRUE(�ѷ���) */
	VisitFunc(G.vertices[v].data); /* ���ʵ�v������ */
	for(w=FirstAdjVex(G,G.vertices[v].data);w>=0;w=NextAdjVex(G,G.vertices[v].data,G.vertices[w].data))
		if(!visited[w])
			DFS(G,w); /* ��v����δ���ʵ��ڽӵ�w�ݹ����DFS */
}

/* ��ͼG��������ȱ������㷨7.4 */
void DFSTraverse(ALGraph G,Status (*Visit)(VertexType v))
{
	int i;
	VisitFunc=Visit; /* ʹ��ȫ�ֱ���VisitFunc,ʹDFS�����躯��ָ����� */
	for(i=0;i<G.vexnum;i++)
		visited[i]=FALSE; /* ���ʱ�־�����ʼ�� */
	for(i=0;i<G.vexnum;i++)
		if(!visited[i])
			DFS(G,i); /* ����δ���ʵĶ������DFS */
	printf("\n");
}

/*��������ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited���㷨7.6 */
void BFSTraverse(ALGraph G,Status (*Visit)(VertexType v))
{
	int i,j,w;
	SqQueue Q;
	
	for(i=0;i<G.vexnum;i++)
		visited[i]=FALSE; /* �ó�ֵ */
	InitQueue(&Q); /* �ÿյĸ�������Q */
	for(i=0;i<G.vexnum;i++) /* �������ͨͼ,ֻv=0�ͱ���ȫͼ */
		if(!visited[i]) /* v��δ���� */
		{
			visited[i]=TRUE;
			Visit(G.vertices[i].data);
			EnQueue(&Q,i); /* v����� */
			while(!QueueEmpty(Q)) /* ���в��� */
			{
				DeQueue(&Q,&j); /* ��ͷԪ�س��Ӳ���Ϊu */
				for(w=FirstAdjVex(G,G.vertices[j].data);w>=0;w=NextAdjVex(G,G.vertices[j].data,G.vertices[w].data))
					if(!visited[w]) /* wΪu����δ���ʵ��ڽӶ��� */
					{
						visited[w]=TRUE;
						Visit(G.vertices[w].data);
						EnQueue(&Q,w); /* w��� */
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