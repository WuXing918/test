#ifndef PROXYSUBJECT_H
#define PROXYSUBJECT_H
#include "Subject.h"

class ConcreteSubject;

class ProxySubject : public Subject
{
public:
    ProxySubject();
    ~ProxySubject();

    virtual void Request();
private:
    ConcreteSubject* m_concreteSubject;
};

#endif // PROXYSUBJECT_H
