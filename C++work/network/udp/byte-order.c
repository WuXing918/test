#include <stdio.h>

int main()
{
	short num = 1;
	char *p = &num;
	printf("%p:",p);
	printf("%d\n",*p);
	printf("%p:",(p+1));
	printf("%d\n",*(p+1));
	
}
