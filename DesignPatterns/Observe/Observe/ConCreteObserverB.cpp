#include "ConCreteObserverB.h"

ConCreteObserverB::ConCreteObserverB(Subject *pSubject)
    : m_pSubject(pSubject)
{

}

void ConCreteObserverB::Update(int value)
{
     cout<<"ConCreteObserverB get the update. New State:"<<value<<endl;
}
