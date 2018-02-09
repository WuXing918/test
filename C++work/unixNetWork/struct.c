#include <stdio.h>

#define	NUM	10
/*** struct of having a name */
struct Node
{
	int data;
	char buf[NUM];
};
typedef struct Node iNode;

/***struct of not having a name 
struct 
{
	int data;
	char buf[NUM];
}node;
***/

int main()
{
	iNode node;
	node.data = 100;
	node.buf = "wuxing";
	printf("data = %dbuf = %s\n", node.data, node.buf);
}

