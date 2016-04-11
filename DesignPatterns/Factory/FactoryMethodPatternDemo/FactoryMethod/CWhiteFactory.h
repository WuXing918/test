#ifndef CWHITEFACTORY_H
#define CWHITEFACTORY_H
#include "IHumanFactory.h"

class CWhiteHuman;


class CWhiteFactory :public IHumanFactory
{
public:
    CWhiteFactory();
    ~CWhiteFactory();
    IHuman* CreateHuman();
};

#endif // CWHITEFACTORY_H
