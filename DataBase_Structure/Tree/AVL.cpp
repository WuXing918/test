#include <iostream>

/***********************************************************************************************
    1. 首先插入，同二叉排序树的插入方法。
    补充：
        插入节点之前，树是平衡二叉树。
        插入之后有可能树不平衡，也有可能保持平衡。
        插入节点的位置一定是叶子节点。
************************************************************************************************/
/***********************************************************************************************
    2. 查找是否平衡的方法是，从插入的位置开始，向上判断其父结点的左右子树是否平衡，一直遍历到root节点。
************************************************************************************************/
/***********************************************************************************************
    声明：
        插入节点之前，树是平衡二叉树。
        插入节点的位置一定是叶子节点。

    3. 判断插入节点的位置是不平衡节点的左子树还是右子树？
       左子树的场合：
           不平衡节点的左子树深度比右子树深度大于1的场合：
                采用左左旋转的方法，矫正平衡。
           上即以外的场合：
                采用左右两次旋转方法，矫正平衡。
       右子树的场合：
           不平衡节点的右子树深度比左子树深度大于1的场合：
                采用右右旋转的方法，矫正平衡。
           上即以外的场合：
                采用右左两次旋转方法，矫正平衡。       
************************************************************************************************/



struct AVLNode {
    int data;
    AVL_Node* lchild;
    AVL_Node* rchild;

 AVLNode(int data, int bf): data(data), bf(bf), lchild(NULL), rchild(NULL) {} 
~AVLNode(){}      
};

class CAVLTree{
private:
   AVLNode* root;
 
public:
    //默认构造函数  
    CAVLTree();
    //析构函数  
    ~CAVLTree();

    //插入节点
    void insertNode(AVLNode *Toot, AVLNode *pNewNode);
    //插入AVL树  
    void insertAVL(AVLNode *Toot, int value));
    
    
};

CAVLTree::CAVLTree(): root(NULL) { }
CAVLTree:~CAVLTree() {}

void CAVLTree::CAVLTreeMidOrderTraverse(AVLTree T)
{
    if (T)
    {
        PreOrderTraverse(T->lchild);
        cout << T->data << " ";
        PreOrderTraverse(T->rchild);
    }
}

void CAVLTree::insertNode(AVLNode *Toot, AVLNode *pNewNode) {
    if (Toot == NULL) {
        Toot = pNewNode;
        return Toot;
    }

    if (pNewNode->data < Toot->data) {
        insertNode(Toot->lchild, pNewNode)
    }
    else {
        insertNode(Toot->lchild, pNewNode)
    }
    
}

void CAVLTree::insertAVL(AVLNode *Toot, int value) {
    AVLNode * pNewNode = new AVLNode(value, 0);

    // 需要插入的元素小于根节点
    insertNode(Toot, pNewNode);
}


int main() {
    CAVLTree tree;
    tree->insert();
}














