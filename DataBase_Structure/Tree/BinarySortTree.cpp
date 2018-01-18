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
    void Preprint(Node* root);
    void Postprint(Node* root);
   
public:

    Tree():root(NULL) {}
    ~Tree(){}

public:

    void InorderInsert(Tree* tree, int num);    
    void InorderPrint(Tree* tree);
    void InPrePrint(Tree* tree);
    void InPostPrint(Tree* tree);
   
};

// 二叉排序排序树
void Tree::InorderInsert(Tree* tree, int num) {
    Node *temp = new Node(num);
    
    if(root == NULL) {
        root = temp;
        return;        
    }
    // 声明 查找插入的位置指针， 插入的位置一定是叶子节点的子节点
    Node* head = tree->root;
    // 声明插入之位置节点的父结点（即叶子节点）
    Node* flag = head;
    //循环查找
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

void Tree::Preprint(Node* root) {
    if (root) {
	cout << root->data <<" ";
	Preprint(root->left);
        Preprint(root->right);
    }
}

 void Tree::InPrePrint(Tree* tree) {
    Node * head = tree->root;
    Preprint(head);
    cout << endl;
}

void Tree::Postprint(Node* root) {
    if (root) {	
	Postprint(root->left);
    Postprint(root->right);
    cout << root->data <<" ";
    }
}

 void Tree::InPostPrint(Tree* tree) {
    Node * head = tree->root;
    Postprint(head);
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
    tree->InPrePrint(tree);
    tree->InPostPrint(tree);
    
    
}












