#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
int main()
{
	/*int *a = mmap(
		0,
		4,
		PROT_READ|PROT_WRITE,
		MAP_ANONYMOUS|MAP_PRIVATE,
		0,
		0
		);
	*/
	//int *a = sbrk(4);
	int *a = mmap(
		0,
		4,
		PROT_READ|PROT_WRITE,
		MAP_ANONYMOUS|MAP_SHARED,
		0,
		0
		);
	*a = 100;
	if(fork()==0)
	{
			printf("parent \n");
			printf("%d\n",*a);
			*a = 900;
			printf("%d\n",*a);
	}else{
			printf("child \n");
			printf("%d\n",*a);
			sleep(5);
			printf("%d\n",*a);
	}
}
