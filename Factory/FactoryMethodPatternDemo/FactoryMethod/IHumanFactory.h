/*
*
*
*/
#ifndef IHUMANFACTORY_H
#define IHUMANFACTORY_H
#include "IHuman.h"

class IHumanFactory
{
public:
    IHumanFactory();
    ~IHumanFactory();

    public:
    virtual IHuman* CreateHuman() = 0;
};

#endif // IHUMANFACTORY_H
