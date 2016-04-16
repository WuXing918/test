#include "HuanMaoStore.h"
#include <iostream>
using namespace std;
HuanMaoStore::HuanMaoStore():
    m_Price(0)
  , m_Num(0)
{

}

HuanMaoStore::~HuanMaoStore()
{

}

void HuanMaoStore::SetPrice(int price)
{
    this->m_Price = price;
    cout << "HuanMaoStore m_Price = " << m_Price <<endl;
}

void HuanMaoStore::SetNum(int num)
{
    this->m_Num = num;
    cout << "HuanMaoStore m_Num = " << m_Num <<endl;
}

