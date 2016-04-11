#ifndef CYELLOWFACTORY_H
#define CYELLOWFACTORY_H
#include "IHumanFactory.h"
class CYellowHuman;

class CYellowFactory : public IHumanFactory
{
public:
    CYellowFactory();
    ~CYellowFactory();
    IHuman* CreateHuman();
};

#endif // CYELLOWFACTORY_H
