#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

int main()
{
	int *p = mmap(
			NULL,//指定映射首地址，0，NULL为系统指定
			getpagesize(),//映射内存的大小
			PROT_READ|PROT_WRITE,//映射的使用权限
			MAP_ANONYMOUS|MAP_SHARED,//映射的方式，匿名映射，和文件映射，共享映射，私有映射等等
			0,//
			0 //
		);

	printf("------------------\n");
	*p = 1000;
	printf("*p = %d\n",*p);
	*(p+1023)=1023;
	printf("*p = %d\n",*(p+1023));
	*(p+1024)=1024;	
	printf("*p = %d\n",*(p+1024));
	

}
