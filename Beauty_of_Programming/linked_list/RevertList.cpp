#include <iostream>
using namespace std;
struct Node {
	int m_data;
	Node* m_next;
	Node(int num):m_data(num),m_next(NULL){}
};

class RevertList 
{
public:
	RevertList():m_point(NULL){}
	~RevertList(){}
	// 单链表反转 
	void revert(){
		// 首先判空
		if (NULL == m_point) {
			return;
		}
		// 定义两个链表指针，一个用来循环遍历，一个用来创建新的链表。
		Node * ptr = m_point;
		Node * temp = NULL;
		while(NULL != m_point) {
			m_point = m_point->m_next;// 遍历
			ptr->m_next = temp;
			temp = ptr;
			ptr = m_point;
		}
		m_point = temp;// 最后将 链表头指针赋值回去！
	}
	void insert(int num) {
		Node *node = new Node(num);
		node->m_next = m_point;
		m_point = node;
	}
	
	void print() {
		Node * temp = m_point;
		while(temp) {
			cout << temp->m_data << " ";
			temp = temp->m_next;
		}
		cout << endl;
	}	



private:
	Node* m_point;
};

int main() {
	RevertList *list = new RevertList();
	list->insert(10);
	list->insert(20);
	list->insert(90);
	list->insert(30);
	list->insert(40);
	list->print();
	list->revert();
	list->print();
}

