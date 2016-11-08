#include <iostream>
using namespace std;


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
    Node* Head;
    Node* Tail;
    int Cache;
    int Count;
};

LRUCache::LRUCache():
Head(),
Tail(),
Cache(),
Count()



//疑问
// 空的双链表怎么表示？
//
