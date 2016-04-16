#include <iostream>
#include "IPhone.h"
#include "Observe.h"
#include "HuanMaoStore.h"
using namespace std;

int main()
{
    IPhone    *m_phone = new IPhone();
    Observe  *m_observe = new HuanMaoStore();
    m_phone->Attach(m_observe);

    m_phone->SetPrice(5288);
    m_phone->Notify();


    return 0;
}

