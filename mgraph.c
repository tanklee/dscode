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


/*ͼ������(�ڽӾ���)�洢��ʾ */
#define INFINITY INT_MAX /* ���������ֵ����� */
#define MAX_VERTEX_NUM 20 /* ��󶥵���� */

#define MAX_NAME 5
#define MAX_INFO 20
typedef int VRType;
typedef char InfoType;
typedef char VertexType[MAX_NAME];

typedef enum{DG,DN,AG,AN}GraphKind; /* {����ͼ,������,����ͼ,������} */
typedef struct
{
	VRType adj; /* �����ϵ���͡�����Ȩͼ����1(��)��0(��)��ʾ���ڷ� */
	            /* �Դ�Ȩͼ��c��ΪȨֵ���� */
	InfoType *info; /* �û������Ϣ��ָ��(����) */
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{
   VertexType vexs[MAX_VERTEX_NUM]; /* �������� */
   AdjMatrix arcs; /* �ڽӾ��� */
   int vexnum,arcnum; /* ͼ�ĵ�ǰ�������ͻ��� */
   GraphKind kind; /* ͼ�������־ */
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
* ��ʼ����:ͼG����,u��G�ж�������ͬ���� 
* �������:��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1 
*/
int LocateVex(MGraph G,VertexType u)
{
	int i;
	for(i=0;i<G.vexnum;i++)
		if(strcmp(u,G.vexs[i])==0)
			return i;
	return -1;
}


/* ��������(�ڽӾ���)��ʾ��,��������ͼG */
Status CreateDG(MGraph *G)
{ 
	int i,j,k,l,IncInfo;
	char s[MAX_INFO],*info;
	VertexType va,vb;

	printf("����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
	scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);

	printf("������%d�������ֵ(<%d���ַ�):\n",(*G).vexnum,MAX_NAME);
	for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
		scanf("%s",(*G).vexs[i]);
	for(i=0;i<(*G).vexnum;++i) /* ��ʼ���ڽӾ��� */
		for(j=0;j<(*G).vexnum;++j)
		{
			(*G).arcs[i][j].adj=0; /* ͼ */
			(*G).arcs[i][j].info=NULL;
		}

	printf("������%d�����Ļ�β ��ͷ(�Կո���Ϊ���): \n",(*G).arcnum);
	for(k=0;k<(*G).arcnum;++k)
	{
		scanf("%s%s%*c",va,vb);  /* %*c�Ե��س��� */
		i=LocateVex(*G,va);
		j=LocateVex(*G,vb);
		(*G).arcs[i][j].adj=1; /* ����ͼ */
		if(IncInfo)
		{
			printf("������û��������Ϣ(<%d���ַ�): ",MAX_INFO);
			gets(s);
			l=strlen(s);
			if(l)
			{
				info=(char*)malloc((l+1)*sizeof(char));
				strcpy(info,s);
				(*G).arcs[i][j].info=info; /* ���� */
			}
		}
   }

   (*G).kind=DG;
   return OK;
}


/* ��������(�ڽӾ���)��ʾ��,����������G */
Status CreateDN(MGraph *G)
{ 
	int i,j,k,w,IncInfo;
	char s[MAX_INFO],*info;
	VertexType va,vb;

	printf("������������G�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
	scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);

	printf("������%d�������ֵ(<%d���ַ�):\n",(*G).vexnum,MAX_NAME);
	for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
		scanf("%s",(*G).vexs[i]);
	for(i=0;i<(*G).vexnum;++i) /* ��ʼ���ڽӾ��� */
		for(j=0;j<(*G).vexnum;++j)
		{
			(*G).arcs[i][j].adj=INFINITY; /* �� */
			(*G).arcs[i][j].info=NULL;
		}

	printf("������%d�����Ļ�β ��ͷ Ȩֵ(�Կո���Ϊ���): \n",(*G).arcnum);
	for(k=0;k<(*G).arcnum;++k)
	{
		scanf("%s%s%d%*c",va,vb,&w);  /* %*c�Ե��س��� */
		i=LocateVex(*G,va);
		j=LocateVex(*G,vb);
		(*G).arcs[i][j].adj=w; /* ������ */
		if(IncInfo)
		{
			printf("������û��������Ϣ(<%d���ַ�): ",MAX_INFO);
			gets(s);
			w=strlen(s);
			if(w)
			{
				info=(char*)malloc((w+1)*sizeof(char));
				strcpy(info,s);
				(*G).arcs[i][j].info=info; /* ���� */
			}
		}
	}

   (*G).kind=DN;
   return OK;
}


/* ��������(�ڽӾ���)��ʾ��,��������ͼG */
Status CreateAG(MGraph *G)
{
	int i,j,k,l,IncInfo;
	char s[MAX_INFO],*info;
	VertexType va,vb;
	printf("����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
	scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
	
	printf("������%d�������ֵ(<%d���ַ�):\n",(*G).vexnum,MAX_NAME);
	for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
		scanf("%s",(*G).vexs[i]);
	for(i=0;i<(*G).vexnum;++i) /* ��ʼ���ڽӾ��� */
		for(j=0;j<(*G).vexnum;++j)
		{
			(*G).arcs[i][j].adj=0; /* ͼ */
			(*G).arcs[i][j].info=NULL;
		}

   printf("������%d���ߵĶ���1 ����2(�Կո���Ϊ���): \n",(*G).arcnum);
   for(k=0;k<(*G).arcnum;++k)
   {
		scanf("%s%s%*c",va,vb); /* %*c�Ե��س��� */
		i=LocateVex(*G,va);
		j=LocateVex(*G,vb);
		(*G).arcs[i][j].adj=(*G).arcs[j][i].adj=1; /* ����ͼ */
		if(IncInfo)
		{
			printf("������ñߵ������Ϣ(<%d���ַ�): ",MAX_INFO);
			gets(s);
			l=strlen(s);
			if(l)
			{
				info=(char*)malloc((l+1)*sizeof(char));
				strcpy(info,s);
				(*G).arcs[i][j].info=(*G).arcs[j][i].info=info; /* ���� */
			}
		}
   }

   (*G).kind=AG;
   return OK;
}


/* ��������(�ڽӾ���)��ʾ��,����������G���㷨7.2 */
Status CreateAN(MGraph *G)
{ 
	int i,j,k,w,IncInfo;
	char s[MAX_INFO],*info;
	VertexType va,vb;

	printf("������������G�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
	scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);

	printf("������%d�������ֵ(<%d���ַ�):\n",(*G).vexnum,MAX_NAME);
	for(i=0;i<(*G).vexnum;++i) /* ���춥������ */
		scanf("%s",(*G).vexs[i]);
	for(i=0;i<(*G).vexnum;++i) /* ��ʼ���ڽӾ��� */
		for(j=0;j<(*G).vexnum;++j)
		{
			(*G).arcs[i][j].adj=INFINITY; /* �� */
			(*G).arcs[i][j].info=NULL;
		}

	printf("������%d���ߵĶ���1 ����2 Ȩֵ(�Կո���Ϊ���): \n",(*G).arcnum);
	for(k=0;k<(*G).arcnum;++k)
	{
		scanf("%s%s%d%*c",va,vb,&w); /* %*c�Ե��س��� */
		i=LocateVex(*G,va);
		j=LocateVex(*G,vb);
		(*G).arcs[i][j].adj=(*G).arcs[j][i].adj=w; /* ���� */
		if(IncInfo)
		{
			printf("������ñߵ������Ϣ(<%d���ַ�): ",MAX_INFO);
			gets(s);
			w=strlen(s);
			if(w)
			{
				info=(char*)malloc((w+1)*sizeof(char));
				strcpy(info,s);
				(*G).arcs[i][j].info=(*G).arcs[j][i].info=info; /* ���� */
			}
		}
	}

	(*G).kind=AN;
	return OK;
}



/* ��������(�ڽӾ���)��ʾ��,����ͼG���㷨7.1 */
Status CreateGraph(MGraph *G)
{ 
	printf("������ͼG������(����ͼ:0,������:1,����ͼ:2,������:3): ");
	scanf("%d",&(*G).kind);
	switch((*G).kind)
	{
		case DG: return CreateDG(G); /* ��������ͼ */
		case DN: return CreateDN(G); /* ���������� */
		case AG: return CreateAG(G); /* ��������ͼ */
		case AN: return CreateAN(G); /* ���������� */
		default: return ERROR;
   }
}


/* ��ʼ����: ͼG���ڡ��������: ����ͼG */
void DestroyGraph(MGraph *G)
{ 
	int i,j;
	if((*G).kind<2) /* ���� */
	{
		for(i=0;i<(*G).vexnum;i++) /* �ͷŻ��������Ϣ(����еĻ�) */
			for(j=0;j<(*G).vexnum;j++)
				if((*G).arcs[i][j].adj==1&&(*G).kind==0||(*G).arcs[i][j].adj!=INFINITY&&(*G).kind==1) /* ����ͼ�Ļ�||�������Ļ� */
				if((*G).arcs[i][j].info) /* �������Ϣ */
				{
					free((*G).arcs[i][j].info);
					(*G).arcs[i][j].info=NULL;
				}
	}

   else /* ���� */
		for(i=0;i<(*G).vexnum;i++) /* �ͷűߵ������Ϣ(����еĻ�) */
			for(j=i+1;j<(*G).vexnum;j++)
				if((*G).arcs[i][j].adj==1&&(*G).kind==2||(*G).arcs[i][j].adj!=INFINITY&&(*G).kind==3) /* ����ͼ�ı�||�������ı� */
					if((*G).arcs[i][j].info) /* �������Ϣ */
					{
						free((*G).arcs[i][j].info);
						(*G).arcs[i][j].info=(*G).arcs[j][i].info=NULL;
					}

   (*G).vexnum=0;
   (*G).arcnum=0;
}

/* ����ڽӾ���G */
void Display(MGraph G)
{ 
	int i,j;
	char s[7],s1[3];
	switch(G.kind)
	{
		case DG: strcpy(s,"����ͼ\0");
				strcpy(s1,"��\0");
				break;
		case DN: strcpy(s,"������\0");
				strcpy(s1,"��\0");
				break;
		case AG: strcpy(s,"����ͼ\0");
				strcpy(s1,"��\0");
				break;
		case AN: strcpy(s,"������\0");
				strcpy(s1,"��\0");
	}

	printf("%d������%d��%s��%s\n",G.vexnum,G.arcnum,s1,s);
	
	for(i=0;i<G.vexnum;++i) /* ���G.vexs */
		printf("G.vexs[%d]=%s\n",i,G.vexs[i]);
	
	printf("G.arcs.adj:\n"); /* ���G.arcs.adj */
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
			printf("%6d",G.arcs[i][j].adj);
		printf("\n");
	}

	printf("G.arcs.info:\n"); /* ���G.arcs.info */
	printf("����1(��β) ����2(��ͷ) ��%s��Ϣ��\n",s1);
	if(G.kind<2) /* ���� */
		for(i=0;i<G.vexnum;i++)
			for(j=0;j<G.vexnum;j++)
			{
				if(G.arcs[i][j].info)
					printf("%5s %11s     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
			}
   else /* ���� */
   {
	   for(i=0;i<G.vexnum;i++)
			for(j=i+1;j<G.vexnum;j++)
				if(G.arcs[i][j].info)
					printf("%5s %11s     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
   }

}


/* 
* ��ʼ����: ͼG����,v��G��ĳ������ 
* �������: ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ���,�򷵻�-1 
*/
int FirstAdjVex(MGraph G,VertexType v)
{ 
	int i,value=0,k;
	k=LocateVex(G,v); /* kΪ����v��ͼG�е���� */
	if(G.kind==DN||G.kind==AN) /* �� */
		value=INFINITY;
	for(i=0;i<G.vexnum;i++)
		if(G.arcs[k][i].adj!=value)
			return i;
	return -1;
}


/* 
* ��ʼ����: ͼG����,v��G��ĳ������,w��v���ڽӶ��� 
* �������: ����v��(�����w��)��һ���ڽӶ�������, 
*           ��w��v�����һ���ڽӶ���,�򷵻�-1 
*/
int NextAdjVex(MGraph G,VertexType v,VertexType w)
{ 
	int i,value=0,k1,k2;
	k1=LocateVex(G,v); /* k1Ϊ����v��ͼG�е���� */
	k2=LocateVex(G,w); /* k2Ϊ����w��ͼG�е���� */
	if(G.kind==DN||G.kind==AN) /* �� */
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

Boolean visited[MAX_VERTEX_NUM]; /* ���ʱ�־����(ȫ����) */
Status(*VisitFunc)(VertexType); /* �������� */

/* �ӵ�v����������ݹ��������ȱ���ͼG���㷨7.5 */
void DFS(MGraph G,int v)
{ 
	int w;
	visited[v]=TRUE; /* ���÷��ʱ�־ΪTRUE(�ѷ���) */
	VisitFunc(G.vexs[v]); /* ���ʵ�v������ */

	for(w=FirstAdjVex(G,G.vexs[v]);w>=0;w=NextAdjVex(G,G.vexs[v],G.vexs[w]))
		if(!visited[w])
			DFS(G,w);/* ��v����δ���ʵ����Ϊw���ڽӶ���ݹ����DFS */
}


/*
* ��ʼ����: ͼG����,Visit�Ƕ����Ӧ�ú������㷨7.4 
* �������: �ӵ�1��������,������ȱ���ͼG,����ÿ��������ú���Visit 
*  һ���ҽ�һ�Ρ�һ��Visit()ʧ��,�����ʧ��
*/
void DFSTraverse(MGraph G,Status(*Visit)(VertexType v))
{ 
	int v;
	VisitFunc=Visit; /* ʹ��ȫ�ֱ���VisitFunc,ʹDFS�����躯��ָ����� */
	for(v=0;v<G.vexnum;v++)
		visited[v]=FALSE; /* ���ʱ�־�����ʼ��(δ������) */
	for(v=0;v<G.vexnum;v++)
		if(!visited[v])
			DFS(G,v); /* ����δ���ʵĶ������DFS */
	printf("\n");
}


/* 
* ��ʼ����: ͼG����,Visit�Ƕ����Ӧ�ú������㷨7.6 
* �������: �ӵ�1��������,��������ȷǵݹ����ͼG,����ÿ��������ú��� 
*           Visitһ���ҽ�һ�Ρ�һ��Visit()ʧ��,�����ʧ�ܡ� 
*           ʹ�ø�������Q�ͷ��ʱ�־����visited 
*/
void BFSTraverse(MGraph G,Status(*Visit)(VertexType v))
{
	int i,j,w;
	SqQueue Q;
	
	for(i=0;i<G.vexnum;i++)
		visited[i]=FALSE; /* �ó�ֵ */
	InitQueue(&Q); /* �ÿյĸ�������Q */
	
	for(i=0;i<G.vexnum;i++)
		if(!visited[i]) /* v��δ���� */
		{
			visited[i]=TRUE; /* ���÷��ʱ�־ΪTRUE(�ѷ���) */
			Visit(G.vexs[i]);
			EnQueue(&Q,i); /* v����� */
			while(!QueueEmpty(Q)) /* ���в��� */
			{
				DeQueue(&Q,&j); /* ��ͷԪ�س��Ӳ���Ϊu */
				for(w=FirstAdjVex(G,G.vexs[j]);w>=0;w=NextAdjVex(G,G.vexs[j],G.vexs[w]))
				if(!visited[w]) /* wΪu����δ���ʵ��ڽӶ������� */
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
