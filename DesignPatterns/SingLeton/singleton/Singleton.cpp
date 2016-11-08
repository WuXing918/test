#include "Singleton.h"
#include <iostream>
using namespace std;

Singleton* Singleton::m_Instance = NULL;

Singleton* Singleton::GetInstance() 
{
    if (NULL == m_Instance) {
        m_Instance = new Singleton();  
    }
    return m_Instance;
}

void Singleton::DestroyInstance() 
{
    if (NULL != m_Instance) 
    {
        delete m_Instance;
		m_Instance = NULL;
    }

}

void Singleton::print() 
{
	cout << "Singleton" << endl;
} 

Singleton::Singleton() 
{

}

Singleton::~Singleton() 
{

}
