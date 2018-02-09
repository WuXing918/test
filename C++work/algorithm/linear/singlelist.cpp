#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;



struct Node
{
	Node * next;
	int data;
	Node(int da):next(NULL),data(da){}
};

class SingleList
{
	int len;
	Node *head;
public:
	SingleList():len(0),head(NULL){}
	~SingleList(){}
	void insert(){
		int num;
		cout <<"请输入数据:";
		cin >>num;
		Node *p =new Node(num);
		p->next = head;
		head = p;
		len++;
	}
	bool earse(){
	
		int num;
		cout <<"请输入要删除的数据:";
		cin >> num;
		Node *find = head;
		if(find==NULL){
			cout <<"链表为空！";
			return false;
		}
		Node *p = find;
		while(find!=NULL&&find->data!=num)
		{
			p = find;
			find = find->next;
		}
		if(find==NULL)
		{
			cout <<"没有该数据！"<<endl;
			return false;
		}else if(p==find){
			head = find->next;
			delete find;
			len--;
			return true;
		}else{
			p->next = find->next;
			delete find;
			len--;
			return true;
		}
	}
	
	void print(){
		Node *p = head;
		while(p)
		{
			cout<<p->data<<" ";
			p = p->next;
		}
		cout<<endl;
		cout <<"打印结束！"<<endl;
	}
};
int ShowMenu();
int main()
{
	SingleList list;
	while(1){
		switch(ShowMenu())
		{
			case 1: list.insert();break;
			case 2: list.earse();break;
			case 3: list.print();break;
			case 4:cout<<"待定！"<<endl;break;
			case 0:cout<<"谢谢使用，再见！"<<endl;exit(-1);
		}
	}
}
int ShowMenu()
{
	//system("clear");
	int num;
	cout<<"----------------"<<endl;
	cout<<"【1】:插入数据！"<<endl;
	cout<<"【2】:删除数据！"<<endl;
	cout<<"【3】:打印数据！"<<endl;
	cout<<"【4】:待定!"<<endl;
	cout<<"【0】:推出！"<<endl;
	cout<<"----------------"<<endl;
	cout<<"请输入:";
	cin>>num;
	return num%5;
}
