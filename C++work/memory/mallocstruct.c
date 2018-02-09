#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	//malloc参数不超过24个字节的时候，其一次分配32个字节，	
	int *p1=malloc(25);
	int *p2=malloc(4);
	int *p3=malloc(4);
	printf("%p\n",p1);	
	printf("%p\n",p2);	
	printf("%p\n",(p2-p1));	
	*p1=1;
	printf("______________________\n");/*
	*(p1+1)=2;
	*(p1+2)=3;
	*(p1+3)=4;
	*(p1+4)=5;
	*(p1+5)=6;
	*(p1+6)=7;
	*(p1+7)=8;*/
	*(p1+8)=9;
	*(p1+9)=10;
	printf("------\n");
	*(p1+1024)=1024;
	printf("------\n");
	*(p1+2048)=2048;
	printf("------\n");
	*(p1+3072)=3096;
	printf("------\n");
	*(p1+4096)=4096;
	free(p1);			
	printf("%d\n",*p2);
	return 0;
	
}
