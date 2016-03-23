#ifndef CONCRETEFACTORY_H
#define CONCRETEFACTORY_H
#include "factory_global.h"
class UICommonBase;

class ConCreteFactory
{
public:
       static ConCreteFactory* GetInstance();

	UICommonBase*  CreateUICommon(UIC_KIND kind);

private:
    ConCreteFactory();
    
private:
    static ConCreteFactory* m_Instance;
};

#endif // CONCRETEFACTORY_H
