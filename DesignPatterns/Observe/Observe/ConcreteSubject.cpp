#include "ConcreteSubject.h"

void ConcreteSubject::Attach(Observer *pObserver)
{
     m_ObserverList.push_back(pObserver);
}

void ConcreteSubject::Detach(Observer *pObserver)
{
     m_ObserverList.remove(pObserver);
}

void ConcreteSubject::Notify()
{
     std::list<Observer *>::iterator it = m_ObserverList.begin();
     while (it != m_ObserverList.end())
     {
          (*it)->Update(m_iState);
          ++it;
     }
}

void ConcreteSubject::SetState(int state)
{
     m_iState = state;
}

