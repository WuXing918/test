#include <iostream>
using namespace std;

#define LRUCACHECOUNT 10
Struct Node {
    int key;
    string value;
    Node* Prev;
    Node* next;
    Node():key(0),value(0),Prev(NULL),next(NULL){}
};



class LRUCache {
    LRUCache();
    ~LRUCache();



private:
    int Cache; 
    int Count;
    Node* Head; // 把最近刚刚使用的节点或者刚建立的节点放在头节点；
    Node* Tail; // Cache 已满的时候方便去掉尾节点（最近最少使用的那个节点）；
    
};

LRUCache::LRUCache():
    Cache(0),
    Count(LRUCACHECOUNT)
{
    
}


//疑问
// 空的双链表怎么表示？
// 双连表和单链表一样也是由头指针唯一表示
