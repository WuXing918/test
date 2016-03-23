#ifndef FACTORY_H
#define FACTORY_H

#include "factory_global.h"
#include "UICommonBase.h"
class Factory
{

public:
    Factory();
    ~Factory();

    UICommonBase* CreateUICommon(UIC_KIND kind);

};

#endif // FACTORY_H
