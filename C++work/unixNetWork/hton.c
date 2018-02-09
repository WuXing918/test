#include <stdio.h>

typedef int uint32_t;
typedef short uint16_t;

uint32_t netNum1 = 1;
uint16_t netNum2 = 1;
#define	L	3
#define	S	1
int main()
{
	printf("%d\n",htonl(netNum1)>>L);

	printf("%d\n",htons(netNum2)>>S);
}

