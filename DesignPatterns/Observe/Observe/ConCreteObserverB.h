#ifndef CONCRETEOBSERVERB_H
#define CONCRETEOBSERVERB_H

#include "Observer.h"
#include "Subject.h"

class ConCreteObserverB : public Observer
{
public:
     ConCreteObserverB(Subject *pSubject);

     void Update(int value);

private:
     Subject *m_pSubject;
};

#endif // CONCRETEOBSERVERB_H
