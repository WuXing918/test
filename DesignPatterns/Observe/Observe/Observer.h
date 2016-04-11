#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>
#include <list>
using namespace std;

class Observer
{
public:
     virtual void Update(int) = 0;
    ~Observer();
    Observer();
private:

};


#endif // OBSERVER_H
