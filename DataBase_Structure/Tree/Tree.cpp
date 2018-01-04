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
    
    if(root == NULL) {
        root = temp;
        return;        
    }
    // 查找插入的位置
    Node* head = tree->root;
    Node* flag = head;
    while (head) {
        if (head->data >= temp->data) {
	    flag = head;
            head = head->left;    
        }
        else {
            flag = head;
            head = head->right;     
        }
    }
    // 将数据插入
    if(flag->data >= temp->data) {
	flag->left = temp;
    } 
    else {
	flag->right = temp;
    }
}

void Tree::Medprint(Node* root) {
    if (root) {
	Medprint(root->left);
        cout << root->data <<" ";
        Medprint(root->right);
    }
}

 void Tree::InorderPrint(Tree* tree) {
    Node * head = tree->root;
    Medprint(head);
    cout << endl;
}



int main() {

    Tree* tree = new Tree();
    tree->InorderInsert(tree, 1);
    tree->InorderInsert(tree, 8);
    tree->InorderInsert(tree, 7);
    tree->InorderInsert(tree, 6);
    tree->InorderInsert(tree, 5);
    tree->InorderInsert(tree, 4);
    tree->InorderInsert(tree, 2);
    tree->InorderPrint(tree);
   
    
}












