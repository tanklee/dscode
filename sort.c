#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int sqsearch(int a[],int n,int e)
{
	int i;
	for(i=0;i<n;i++)
		if(a[i]==e)
			return i;
	return -1;
}

int bisearch(int a[],int n,int e)
{
	int low,high,mid;
	low=0;
	high=n-1;
	while(low<=high){
		mid=(low+high)/2;
		if(e==a[mid])
			return mid;
		else if(e<a[mid])
			high=mid-1;
		else
			low=mid+1;
	}
	return -1;
}

void InsertSort(int a[],int n)
{
	int i,j,t;
	for(i=1;i<n;i++){
		t=a[i];
		for(j=i-1;j>=0 && a[j]>t;j--)
			a[j+1]=a[j];
		a[j+1]=t;
	}
}

void BiInsertSort(int a[],int n)
{
	int i,j,t,low,high,mid;
	for(i=1;i<n;i++){
		t=a[i];
		low=0;
		high=i-1;
		while(low<=high){
			mid=(low+high)/2;
			if(t<a[mid])
				high=mid-1;
			else
				low=mid+1;
		}
		for(j=i-1;j>high;j--)
			a[j+1]=a[j];
		a[high+1]=t;
	}
}

void BubbleSort(int a[],int n)
{
	int i,j,t;
	for(i=n-2;i>=0;i--){
		for(j=0;j<=i;j++){
			if(a[j]>a[j+1]){
				t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
			}
		}
	}
}

void SelectSort(int a[],int n)
{
	int i,j,minloc,t;
	for(i=0;i<n-1;i++)
	{
		minloc=i;
		for(j=i+1;j<n;j++)
			if(a[j]<a[minloc])
				minloc=j;
		if(minloc!=i)
		{
			t=a[i];
			a[i]=a[minloc];
			a[minloc]=t;
		}
	}

}


void ShellSort(int a[],int n)
{
	int dk;
	int i,j,t;
	for(dk=n/2;dk>0;dk=dk/2)
	{
		for(i=dk;i<n;i++){
			t=a[i];
			for(j=i-dk;j>=0 && t<a[j];j-=dk)
				a[j+dk]=a[j];
			a[j+dk]=t;
		}
	}
}

int Parttion(int a[],int low,int high)
{
	int t=a[low];
	while(low<high)
	{
		while(low<high && a[high]>=t) high--;
		a[low]=a[high];
		while(low<high && a[low]<=t) low++;
		a[high]=a[low];
	}
	a[low]=t;
	return low;
}

void QuickSort(int a[],int low,int high)
{
	int pivotloc;
	if(low<high)
	{
		pivotloc=Parttion(a,low,high);
		QuickSort(a,low,pivotloc-1);
		QuickSort(a,pivotloc+1,high);
	}
}


/*
*
* 前提：a[s-1] -- a[m-1] 除a[s-1]外均满足堆定义
* 功能：进行一趟筛选，调整a[s-1]使a[s-1] -- a[m-1]成为大顶堆 
*
*/
void sift(int a[], int s, int m)
{
	int j,rc;
	rc = a[s-1];					//取第s个元素值 
	for(j=2*s; j<=m; j*=2)			//沿较大的孩子结点向下筛选 
	{
		if(j<m && a[j-1]<a[j]) ++j; //第s个元素的孩子为第j和 j+1个元素 取其大者 
		if(rc >= a[j-1]) 
			break;					//不需要筛选 
		a[s-1] = a[j-1];			//第j个元素取代第s个元素 
		s = j;                      //下次要筛选的起始位序 
	}
	a[s-1] = rc;					//rc最终存放位置 
}

void HeapSort(int a[],int n)
{
	int i,t;
	for(i = n/2; i>0; --i)			//a[0 - n-1]建成大顶堆 ，从最后一个非终端结点开始筛选 
		sift(a,i,n);  				//数组已成堆,a[0]是最大值  
	for(i=n-1;i>0;--i) 
	{
		t = a[0];					//把a[0]和最后元素交换  
		a[0] = a[i];
		a[i] = t;
		sift(a,1,i);				//再次筛选成堆求次大值
	}

}


void display(int a[],int n)
{
	int i;
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
}

int main()
{
	int a[]={15,35,25,45,65,55};
	/*
	InsertSort(a,6);
	BiInsertSort(a,6);
	*/
	//BubbleSort(a,6);
	//SelectSort(a,6);
	//ShellSort(a,6);
	//QuickSort(a,0,5);
	HeapSort(a,6);
	display(a,6);
}
