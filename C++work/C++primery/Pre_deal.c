#include <stdio.h>
/*
	1.#include
	2.#define
	3#ifdef 
*/
#define ADD
#ifdef ADD
#define add(a,b) (a)+(b)
#endif
int main()
{
	int a=10,b=15;
	printf("%d",add(a,b));
}
