#include <iostream>
using namespace std;

#define LRUCACHECOUNT 10
struct DoubleNode {
    int key;
    string value;
    DoubleNode* prev;
    DoubleNode* next;
    DoubleNode():key(0),value(0),prev(NULL),next(NULL){}
};



class LRUCache {
public:
    LRUCache();
    ~LRUCache();
    void LRUCache_print();



private:
    int Cache; 
    int Count;
    DoubleNode* Head; // 把最近刚刚使用的节点或者刚建立的节点放在头节点；
    DoubleNode* Tail; // Cache 已满的时候方便去掉尾节点（最近最少使用的那个节点）;
    
};

LRUCache::LRUCache():
    Cache(0),
    Count(LRUCACHECOUNT)
{
    Head = new DoubleNode();
    Tail = new DoubleNode();

    Head->prev = NULL;
    Head->next = Tail;
    Tail->prev = Head;
    Tail->next = NULL;
}

void LRUCache::LRUCache_print() 
{
    DoubleNode* temp_print = Head;

    while(temp_print != Tail) 
    {
        cout << temp_print->value << " ";
        temp_print = temp_print->next;
    }
    cout << endl;
}


int main() 
{
    LRUCache * cache = new LRUCache();
    cache->LRUCache_print();
}





//疑问
// 空的双链表怎么表示？
// 双连表和单链表一样也是由头指针唯一表示
