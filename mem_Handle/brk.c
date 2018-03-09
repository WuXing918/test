#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{	
	/*sbrk分配内存的时候，首先先判断，维护的指针是否为0？
		如果为0 ，那么得到大块空闲空间的首地址之后，并且把指针+size，
		如果部位0，返回指针精切将指针位置+size
*/
	//如果首次分配内存，那么如果size是0，其不进行映射内存，首次分配内存其size不能为负数，只能为非负数。
	//内存映射是以整个内存页的证书倍来映射的。
	//映射的内存访问时不报错的，但是内部指针后面的内存可以访问但是非法，内部指针之前的内存属于本进程的内存，所以访问属于有效访问。
	int *p = sbrk(4);
	printf("p=%p\n",p);
	*p = 800;
	printf("*p= %d\n",*p);
	*(p+1) = 800;
	printf("*p= %d\n",*(p+1));
	
	//strcpy();
	printf("----------------------sbrk-----------\n");	
	printf("getpagesize = %d\n",getpagesize());
	*(p+1023)=1023;
	printf("*(p+1023)= %d\n",*(p+1023));
	//*(p+1024)=1024;
	//printf("*(p+1024)= %d\n",*(p+1024));
	printf("------------------malloc---------------\n");	
	int *ptr = malloc(4);
	*ptr = 1000;
	printf("ptr = %d\n",*ptr);
	*(ptr+1023)=1023;
	printf("ptr+1023 = %d\n",*(ptr+1023));
	*(ptr+1024)=1024;
	printf("ptr+1024 = %d\n",*(ptr+1024));
	*(ptr+10240)=10240;
	printf("ptr+10240 = %d\n",*(ptr+10240));
	*(ptr+33791)=33791;
	printf("ptr+33791 = %d\n",*(ptr+33791));
	*(ptr+33792)=33792;
	printf("ptr+33792 = %d\n",*(ptr+33792));
	
	
	
	
	
	//sbrk 函数属于申请内存并且返回内存的首地址，而brk属于内存的扩展。两者最好配合使用。
}
