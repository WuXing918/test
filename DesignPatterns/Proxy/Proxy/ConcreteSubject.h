#ifndef CONCRETESUBJECT_H
#define CONCRETESUBJECT_H
#include "Subject.h"

class ConcreteSubject :public Subject
{
public:
    ConcreteSubject();
    ~ConcreteSubject();

    virtual void Request();
};

#endif // CONCRETESUBJECT_H
