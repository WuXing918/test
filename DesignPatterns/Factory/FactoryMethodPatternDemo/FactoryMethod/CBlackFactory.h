#ifndef CBLACKFACTORY_H
#define CBLACKFACTORY_H
#include "IHumanFactory.h"

class CBlackHuman;

class CBlackFactory :public IHumanFactory
{
public:
    CBlackFactory();
    ~CBlackFactory();
    IHuman* CreateHuman();

};

#endif // CBLACKFACTORY_H
