#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;
    Node(int data): 
        data(data), 
        left(NULL), 
        right(NULL)
    {}
    ~Node(){}
};


class Tree {
    Node* root;
private:
    void Medprint(Node* root);
public:

    Tree():root(NULL) {}
    ~Tree(){}

public:

    void InorderInsert(Tree* tree, int num);    
    void InorderPrint(Tree* tree);
};

void Tree::InorderInsert(Tree* tree, int num) {
    Node *temp = new Node(num);
    Node * head = tree->root;
    if(head == NULL) {
        head = temp;
        return;        
    }
    // 查找插入的位置
    while (head) {
        if (head->data >= temp->data) {
            head = head->left;    
        }
        else {
            head = head->right;     
        }
    }
    // 将数据插入
    head = temp;
}

void Tree::Medprint(Node* root) {
    if(root ==NULL) {
		cout <<"tree id empty!"<<endl;
	}
    
    if (root) {
        cout << root->data <<" ";
        Medprint(root->left);
        Medprint(root->right);
    }	
    cout << endl;
}

 void Tree::InorderPrint(Tree* tree) {
    Node * head = tree->root;
    Medprint(head);
}




int main() {

    Tree* tree = new Tree();
    tree->InorderInsert(tree, 9);
    tree->InorderInsert(tree, 8);
    tree->InorderInsert(tree, 7);
    tree->InorderInsert(tree, 6);
    tree->InorderInsert(tree, 5);
    tree->InorderInsert(tree, 4);
    tree->InorderInsert(tree, 2);
    tree->InorderPrint(tree);
    
    
}












