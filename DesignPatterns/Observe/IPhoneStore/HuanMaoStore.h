#ifndef HUANMAOSTORE_H
#define HUANMAOSTORE_H
#include "Observe.h"

class HuanMaoStore : public Observe
{
public:
    HuanMaoStore();
    ~HuanMaoStore();
    void SetPrice(int price);
    void SetNum(int num);

private:
    int m_Price;
    int m_Num;
};

#endif // HUANMAOSTORE_H
