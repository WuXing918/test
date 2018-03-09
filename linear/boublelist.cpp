#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
struct Node 
{
	Node *pre;
	Node *nxt;
	int data;
	Node(int n):pre(NULL),nxt(NULL),data(n){
		cout << "Node" <<endl;
		cout << data << endl;;
	}	
};
class DoubleList
{
	Node *head;
	int len;
public: 
	DoubleList():head(NULL),len(0){}
	~DoubleList(){}
	void insert(){
		int num;
		cout << "请输入需要插入的数据:";
		cin >> num;
		cout << "1" << endl;
		Node *p = new Node(num);
		cout << "2" << endl;
		p->nxt = head;
		cout << "3" << endl;
		p->pre = NULL;
		head->pre = p;
		head = p;
		
	}
	void earse()
	{  
		cout << "删除数据！" <<endl;
	}
	void print()
	{  
		Node *p = head;
		while(p)
		{
			cout << p->data<< " ";
			p = p->nxt;
		}
		cout << endl;
		cout << "打印数据！" <<endl;
	}
};
int ShowMenu()
{
	int num;
	cout <<"双链表"<<endl;
	cout <<"----------------"<<endl;
	cout <<"【1】:插入数据！"<<endl;
	cout <<"【2】:删除数据！"<<endl;
	cout <<"【3】:待定！"<<endl;
	cout <<"【4】:打印数据！"<<endl;
	cout <<"【0】:推出！"<<endl;
	cout <<"----------------"<<endl;
	cout <<"请输入:";
	cin >> num;
	return num%5;
}
void OnShow(DoubleList *list)
{
	while(1)
	{
		switch(ShowMenu())
		{
			case 1:list->insert();break;
			case 2:list->earse();break;
			case 3:cout <<"备用选项！"<<endl;break;
			case 4:list->print();break;
			case 0: cout <<"谢谢您的使用，再见！"<<endl;exit(-1);
		}
	}
}
int main()
{
	DoubleList *list;
	OnShow(list);
}
