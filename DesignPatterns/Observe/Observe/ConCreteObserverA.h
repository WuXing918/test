#ifndef CONCRETEOBSERVERA_H
#define CONCRETEOBSERVERA_H

#include "Observer.h"
#include "Subject.h"

class ConCreteObserverA : public Observer
{
public:
     ConCreteObserverA(Subject *pSubject);

     void Update(int value);

private:
     Subject *m_pSubject;
};



#endif // CONCRETEOBSERVERA_H
