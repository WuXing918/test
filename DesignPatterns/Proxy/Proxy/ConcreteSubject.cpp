#include "ConcreteSubject.h"
#include <iostream>
using namespace std;


ConcreteSubject::ConcreteSubject()
{

}

ConcreteSubject::~ConcreteSubject()
{

}

void ConcreteSubject::Request()
{
    cout << "ConcreteSubject::Request()" << endl;
}
