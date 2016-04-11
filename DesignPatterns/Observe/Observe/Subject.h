#ifndef SUBJECT_H
#define SUBJECT_H
#include "Observer.h"

class Subject
{
public:
    virtual ~Subject();
     virtual void Attach(Observer *) = 0;
     virtual void Detach(Observer *) = 0;
     virtual void Notify() = 0;
    virtual void SetState(int) = 0;
    Subject();
};

#endif // SUBJECT_H
