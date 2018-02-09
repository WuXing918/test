#include <stdio.h>
#include <unistd.h>
//打印数组
void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
} 
void print(int *a,int len)
{
	int i;
	for( i = 0;i < len;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
}
//插入排序
void insert(int *a,int len)
{
	printf("插入排序！\n");
	int i;
	for(i=1;i<=len;i++)
	{
		int temp = a[i];//未排序的第一个数。
		int loc = i-1;  //要插入的位置前一个
		while(loc>=0&&a[loc]>temp)
		{
			a[loc+1]=a[loc];
			loc--;
		}
		a[loc+1]=temp;
	}
}

//快速排序
void quick(int *a,int len)
{
	if(len<1)return;
	int l = 0;
	int r = len-1;
	while(l<r)
	{
		while((a[l]<a[r])&&(l<r))r--;
		swap((a+l),(a+r));	
		while((a[l]<a[r])&&(l<r))l++;
		swap(a+l,a+r);	
	}
	sleep(2);
	quick(a,l);
	quick(a+l+1,len-l-1);
}
//冒泡排序
void mybubble(int *a,int len)
{
	printf("%d,a[0]=%d\n",len,a[0]);
	printf("my bubble sort,冒泡排序！\n");
	for(int i=0;i<len;i++)
	{
		printf("i=%d  ",i);
		for(int j=i+1;j<len;j++)
		{
			printf("%d%d ",a[i],a[j]);
			if(a[i]>a[j])
			{
				int temp = a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
		printf("\n");
		print(a,10);
	}
	print(a,10);

}
void right_bubble(int *a,int len)
{
	printf("right bubble sort!\n");
	for(int i=0;i<len;i++)
	{
		for(int j=0;j<len-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				int temp = a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
	print(a,10);
}
void left_bubble(int*a,int len)
{
	printf("left bubble sort!\n");
	for(int i=0;i<len;i++)
	{
		for(int j=len-1;j>i;j--)
		{
			if(a[j]<a[j-1])
			{
				int temp = a[j];
				a[j]=a[j-1];
				a[j-1]=temp;
			}
		}
	}
	print(a,len);

}
//选择排序
void select(int *a,int len)
{
	printf("选择排序！\n");
	for(int i=0;i<len;i++)
	{
		int temp=i;//记录最小数的位置
		for(int j=i+1;j<len;j++)
		{
			if(a[temp]>a[j])
			{
				temp = j;
			}
		}
		if(temp!=i)
		{
			int swap = a[temp];
			a[temp] = a[i];
			a[i] = swap;
		}
	}
	print(a,10);


}
int main()
{
	int a[10]={3,9,6,5,7,8,2,1,4,0};
	print(a,10);
	//mybubble(a,10);
	//right_bubble(a,10);
	//left_bubble(a,10);
	//select(a,10);	
	//insert(a,10);
	quick(a,10);
	print(a,10);	
}
