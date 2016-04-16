#ifndef IPHONE_H
#define IPHONE_H
#include <list>
#include "Observe.h"
#include "Subject.h"
class IPhone : public Subject
{
public:
    IPhone();
    ~IPhone();
    virtual void Attach(Observe* pObserver);
    virtual void Detach(Observe* pObserver);
    virtual void Notify();
    virtual void SetPrice(int price);
    virtual void SetNum(int num);
private:
    int m_Price;
    int m_Num;
    std::list<Observe*> m_ObserverList;
};

#endif // IPHONE_H
