#include "ProxySubject.h"
#include "ConcreteSubject.h"
#include <iostream>
using namespace std;

ProxySubject::ProxySubject()
{

}

ProxySubject::~ProxySubject()
{
    if (NULL != m_concreteSubject){
        delete m_concreteSubject;
        m_concreteSubject = NULL;
    }
}

void ProxySubject::Request()
{
    cout << "ProxySubject::Request()" <<endl;

    if(NULL == m_concreteSubject) {
        m_concreteSubject = new ConcreteSubject();
    }

    m_concreteSubject->Request();
}

