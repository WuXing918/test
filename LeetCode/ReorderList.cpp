#include <iostream>
#include <string>
using namespace std;

struct Node {
	int jobID;
	string value;
	Node* next;
	Node(int jobID, string value = "wuxing"):
		jobID(jobID),
		value(value),
		next(NULL) {} 
};

class ReorderList {
public:
	ReorderList():nodecount(0), head(NULL) {}
	~ReorderList(){}
	void print() {
		Node* temp = head;
		while (temp) {
			cout << temp->jobID << " : " << temp-> value << endl;
			temp = temp->next;
		}
		cout << endl;
	}
	
	void insert(int jobID) {
		Node* node = new Node(jobID);
		if (node != NULL) {
			node->next = head;
			head = node;
		}
		else {
			return;
		}
	}
	void Reorder(Node* point) {
		if (point == NULL || point->next == NULL) {
			return;
		}
		cout << "NOT NULL" << endl;
		Node* prev = head;
		Node* last = head->next;
		point = NULL;
		while(last) {
			prev->next = point;
			point = prev;
			prev = last;
			last = last->next;
		}	
		prev->next = point;
		point =  prev;
	}
	Node* getHead() {
		if (head != NULL) {
			cout << "head != NULL" <<endl;
			cout << "---------------------" << endl;
			return head;
		}
		cout << "head == NULL" << endl;
		return head;
	}
	void Reorderlist() {
		

	}
	
private:
	int nodecount;
	Node* head;	
};
int main() 
{
	ReorderList *Rlist = new ReorderList();
	Rlist->insert(1);
	Rlist->insert(2);
	Rlist->insert(3);
	Rlist->insert(4);
	Rlist->insert(5);
	Rlist->insert(6);
	Rlist->insert(7);
	Rlist->insert(8);
	Rlist->insert(9);
	Rlist->insert(10);
	Rlist->insert(11);
	Rlist->insert(12);
	Rlist->insert(13);
	Rlist->insert(14);
	Rlist->insert(15);
	Rlist->insert(16);
	Rlist->insert(17);
	Rlist->insert(18);
	Rlist->insert(19);
	Rlist->insert(20);
	
	Rlist->print();
	Node *temp = Rlist->getHead();
	cout << "---------------------------------------------" << endl;	
	Rlist->Reorder(temp);
	Rlist->print();
	Node *node = new Node(1, "nihao");
	cout << node->value << endl;
		
}
