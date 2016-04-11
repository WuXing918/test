#include "ConCreteObserverA.h"

ConCreteObserverA::ConCreteObserverA(Subject *pSubject)
    : m_pSubject(pSubject)
{

}

void ConCreteObserverA::Update(int value)
{
     cout<<"ConCreteObserverA get the update. New State:"<<value<<endl;
}
