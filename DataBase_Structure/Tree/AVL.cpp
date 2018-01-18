#include <iostream>
/*
    1. 平衡二叉树就是BST树插入的时候，可能存在不平衡的case，出现不平衡的case的场合调整平衡。

    2. BST树插入节点的时候，节点都是插在叶子节点上的。

    3. 节点插入的位置，该位置的父亲节点没有兄弟则会出现不平衡的现象。有四种case。
        1.1 父亲节点为左节点（没有右兄弟）插入的位置为父结点的左孩子位置
        1.2 父亲节点为左节点（没有右兄弟）插入的位置为父结点的右孩子位置
        1.3 父亲节点为右节点（没有左兄弟）插入的位置为父结点的左孩子位置
        2.2 父亲节点为右节点（没有左兄弟）插入的位置为父结点的右孩子位置
*/


struct AVL_Node {
    int data;
    int bf;      // balance flag
    AVL_Node* lchild;
    AVL_Node* rchild;
        
};

void R_Rotate(AVL_Node* p) {


}
