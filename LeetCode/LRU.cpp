#include <iostream>
using namespace std;

#define LRUCACHECOUNT 10
struct DoubleNode {
    int     key;
    char  value;
    DoubleNode* prev;
    DoubleNode* next;
    DoubleNode(int key,char value):key(key),value(value),prev(NULL),next(NULL){}
};



class LRUCache {
public:
    LRUCache();

    ~LRUCache();
    void LRUCache_print();
    DoubleNode* get(int key, char value);
    void AbandomTail();
    void detach(DoubleNode *node);
    void attach(DoubleNode *node);

private:
    int cache; 
    int count;
    DoubleNode* Head; // 把最近刚刚使用的节点或者刚建立的节点放在头节点；
    DoubleNode* Tail; // Cache 已满的时候方便去掉尾节点（最近最少使用的那个节点）;
    
};

LRUCache::LRUCache():
    cache(LRUCACHECOUNT),
    count(2)
{
    cout << "LRU" << endl;
    Head = new DoubleNode(1, 'A');
    Tail = new DoubleNode(2, 'B');
    cout << "LRU new" << endl;
    if (Head == NULL || Tail == NULL) {
    }
    else {
        Head->prev = NULL;
        Head->next = Tail;
        Tail->prev = Head;
        Tail->next = NULL;
    }
    cout << "is NULL" << endl;
}

void LRUCache::LRUCache_print() 
{
    DoubleNode* temp_print = Head;

    while(temp_print != Tail) {
        cout << temp_print->key << " : " << temp_print->value << endl;;
        temp_print = temp_print->next;
    }
    cout << temp_print->key << " : " << temp_print->value << endl;;
}

void LRUCache::AbandomTail() 
{
    Tail = Tail->prev;
    Tail->next->prev = NULL;
    delete Tail->next;
    Tail->next = NULL;
    cout << count << endl; 
    count --;
    cout << count << endl;
}

void LRUCache::detach(DoubleNode *node) {
    if (node->next == NULL) {
        cout << "node is Tail" << endl;             
        node->prev->next = node->next;
        node->prev = NULL;
        node->next = NULL;   
        cout << count << endl; 
        count --;
        cout << count << endl;
    }
    else if (node->prev == NULL) {
        cout << "node is head" << endl;
        node->next->prev = NULL;        
        Head = node->next;
        node->prev = NULL;
        node->next = NULL;   
        cout << count << endl; 
        count --;
        cout << count << endl;        
    }
    else {
        cout << "node is body" << endl;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->prev = NULL;
        node->next = NULL;   
        cout << count << endl; 
        count --;
        cout << count << endl;  
    }
    cout << "LRUCache::detach(DoubleNode *node) is over" << endl;
}


void LRUCache::attach(DoubleNode *node) {
    cout << "void LRUCache::attach(DoubleNode *node) is start !" << endl;
    node->prev = NULL;
    Head->prev = node;
    node->next = Head;
    Head = node;
    cout << count << endl; 
    count ++;
    cout << count << endl;
    cout << "void LRUCache::attach(DoubleNode *node) is end !" << endl;
}

DoubleNode* LRUCache::get(int key, char value) 
{
    cout << key << " : " <<  value << endl;
    if (Head == Tail) {
        cout << "cache is empty" << endl;
    }
    DoubleNode* temp_get = Head;
    while(temp_get != Tail) {
        if(temp_get->key == key) {
            // the key is in the Cache
            cout << "the key is in the Cache" << endl;                
            detach(temp_get);
            cout << temp_get->key << " : " << temp_get->value << endl;
            attach(temp_get);
            break;        
        }
        temp_get = temp_get->next;
    }
    
    if(temp_get != Tail) {
        cout << "the key is in the Cache" << endl;        
    }
    else {
        // The key is not in the Cache
        cout << "The key is not in the Cache" << endl;
        DoubleNode* node = new DoubleNode(key, value);
        
        if (count < cache) {
            // the cache is not full
            cout << "the cache is not full" << endl;            
            attach(node);
        }
        else {
            // the cache is full
            cout << "the cache is full" << endl;
            AbandomTail();         
            attach(node);
        }
        

    }
    
    
    
    
}

int main() 
{
    cout << "START MAIN" <<endl;
    LRUCache *Lcache = new LRUCache();
    cout << "START cache" <<endl;
    if(Lcache) {
        cout << "not NULL" <<endl;
        Lcache->LRUCache_print();
    }
    cout << "-------------------------" << endl;
    Lcache->LRUCache_print();
    Lcache->get(1,'A');
    Lcache->LRUCache_print();
    cout << "-------------------------" << endl;
    cout << "=========================" << endl;
    Lcache->get(3,'C');
    Lcache->LRUCache_print(); 
    Lcache->get(4,'D');
    Lcache->get(5,'E');
    Lcache->get(6,'F');
    Lcache->get(7,'G');
    Lcache->get(8,'H');
    Lcache->get(9,'I');
    Lcache->LRUCache_print();
    Lcache->get(10,'J');
    Lcache->LRUCache_print();
    Lcache->get(11,'K');
    Lcache->LRUCache_print();
    
}





//疑问
// 空的双链表怎么表示？
// 双连表和单链表一样也是由头指针唯一表示
