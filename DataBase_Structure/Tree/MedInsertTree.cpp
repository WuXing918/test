#include <iostream>
#include <stack>
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

    void UnMedInsert(Tree* tree, int num);    
    void MedPrint(Tree* tree);
    void UnMedPrint(Tree* tree);
   
};

void Tree::UnMedInsert(Tree* tree, int num) {
    Node *temp = new Node(num);
    
    if(root == NULL) {
        root = temp;
        return;        
    }
    // 查找插入的位置
    Node* head = tree->root;
    // 插入的位置
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

 void Tree::MedPrint(Tree* tree) {
    Node * head = tree->root;
    Medprint(head);
    cout << endl;
}

// 非递归的中续遍历
void Tree::UnMedPrint(Tree* tree) {
    stack<Node *> list;
    Node* temp = root;
    if (root == NULL) {
        cout << "root is NULL" << endl;
    }

    while(temp || !list.empty()) {
        while(temp) {
            list.push(temp);
            temp = temp->left;
        }
        temp = list.top();
        list.pop();
        cout << temp->data << " ";
        temp = temp->right;
    } 
    cout << endl; 
}

int main() {

    Tree* tree = new Tree();
    tree->UnMedPrint(tree);
    tree->UnMedInsert(tree, 1);
    tree->UnMedInsert(tree, 8);
    tree->UnMedInsert(tree, 7);
    tree->UnMedInsert(tree, 6);
    tree->UnMedInsert(tree, 5);
    tree->UnMedInsert(tree, 4);
    tree->UnMedInsert(tree, 2);
    tree->MedPrint(tree);
    tree->UnMedPrint(tree);
   
    
}












