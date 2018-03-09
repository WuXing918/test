#include <stdio.h>
#include <string.h>
typedef struct Node
{
	char data[20];
	char *next;
}listNode;
struct Node *head = NULL;

void insert(/*Node* head,*/char* num)
{
	printf("1");
	// init node
	struct Node node;
	printf("1");
	strcpy(node.data,num);
	printf("1");
	node.next = NULL;
	printf("1");
	//insert node
	node.next = head;
	head = &node;
}
void print()
{
	while(head)
	{
		printf("%s ",head->data);
		head = head->next;
	}
	printf("\nprint end！\n");
}

int main()
{
	printf("single list start!\n");
	insert("wuxing");
	insert("zhouchen");
	insert("luorong");
	insert("yaodandan");
	insert("huashao");
	print();
	
}
