#include "IPhone.h"
#include "Observe.h"

IPhone::IPhone():
    m_Price(0),
    m_Num(0)
{

}

IPhone::~IPhone()
{

}

void IPhone::Attach(Observe* pObserver)
{
    m_ObserverList.push_back(pObserver);
}

void IPhone::Detach(Observe* pObserver)
{
    m_ObserverList.remove(pObserver);
}

void IPhone::Notify()
{
    std::list<Observe*>::iterator its = m_ObserverList.begin();
    while (its != m_ObserverList.end()) {
        (*its)->SetPrice(m_Price);
        its ++;
    }
}

void IPhone::SetPrice(int price)
{
    this->m_Price = price;
}

void IPhone::SetNum(int num)
{
    this->m_Num = num;
}

