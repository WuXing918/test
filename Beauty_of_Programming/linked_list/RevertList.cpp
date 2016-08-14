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
	// 找到倒数第K个节点
	bool findNode(int k);
	// 删掉指定节点
	bool deleteNode(Node*);
	// 但链表排序（选择排序）
	void selectSort();
	// 单链表反转 
	void revert();
	// 但链表插入
	void insert(int num);
	// 但链表打印
	void print();
	



private:
	Node* m_point;
	int length;
};

bool RevertList::findNode(int k) {
	// 判断链表长度是否比k大
	if (NULL == m_point) {
		return false;
	}
	Node* temp1 = m_point; 
	Node* temp2 = m_point;
	int i = 0;
	for (i = 0; i< k && NULL != temp2; i++) {
		temp2 = temp2->m_next;		
	}
	if (i < k) {
		return false;
	}
	while(temp2) {
		temp2 = temp2->m_next;
		temp1 = temp1->m_next;
	}
	cout << temp1->m_data << endl;
	return true;
}

bool RevertList::deleteNode(Node* m_delNode) 
{
	if (NULL == m_delNode) {
		cout << "NULL == m_delNode" <<endl;
		return false;
	}
	if (NULL == m_delNode->m_next) {
		cout << "RevertList::deleteNode(Node* m_delNode)" << "NULL == m_delNode->m_next" <<endl;
		Node* m_circle = m_point;
		while(m_circle) {
			if(m_circle->m_next == m_delNode) {
				break;
			}
			m_circle = m_circle->m_next;
		}
		if (NULL != m_circle) {
			Node* temp = m_circle->m_next;
			m_circle->m_next = temp->m_next;
			if (NULL != temp) {
				delete temp;
				temp == NULL;
			}
			return true;
		}
		else{
			cout << "RevertList::deleteNode(Node* m_delNode)" << "The Node is not found" <<endl;
			return false;
		}
	}
	else {
		Node * temp = m_delNode->m_next;
		m_delNode->m_data = m_delNode->m_next->m_data;
		m_delNode->m_next = temp->m_next;
		if (NULL != temp) {
			delete temp;
			temp = NULL;
		}
		return true;
	}
}

void RevertList::selectSort()
{
	// 判空
	if (NULL == m_point) {
		return;
	}
	Node *m_smallPtr = m_point;
	Node *m_comparationNum = m_point;
	Node *m_comparationItem = m_point; 
	for (m_comparationNum; m_comparationNum != NULL; m_comparationNum = m_comparationNum->m_next) {
		m_smallPtr = m_comparationNum;
		for (m_comparationItem = m_comparationNum->m_next; m_comparationItem != NULL; m_comparationItem = m_comparationItem->m_next) {
			if(m_smallPtr->m_data > m_comparationItem->m_data) {
				m_smallPtr = m_comparationItem;
			}
		}
		if (m_smallPtr != m_comparationNum) {
			cout << "needs to change" << endl;
			int temp = m_smallPtr->m_data;
			m_smallPtr->m_data = m_comparationNum->m_data;
			m_comparationNum->m_data = temp;
		}
		cout << "----------------------" << endl;
		print();
		cout << "----------------------" << endl;
	}
}

void RevertList::revert(){
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

// 但链表插入
void RevertList::insert(int num) {
	Node *node = new Node(num);
	node->m_next = m_point;
	m_point = node;
}

// 但链表打印
void RevertList::print() {
	Node * temp = m_point;
	while(temp) {
		cout << temp->m_data << " ";
		temp = temp->m_next;
	}
	cout << endl;
}	


int main() {
	RevertList *list = new RevertList();
	list->insert(10);
	list->insert(20);
	list->insert(90);
	list->insert(30);
	list->insert(40);
	// list->print();
	// list->selectSort();
	list->print();
	list->revert();
	list->print();
	cout << "call the selsectSort()" << endl;
	list->selectSort();
	list->print();
	list->findNode(3);
}

