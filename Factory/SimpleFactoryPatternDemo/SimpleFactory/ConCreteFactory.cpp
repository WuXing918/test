#include "ConCreteFactory.h"
#include "factory_global.h"
#include "UICommonPhone.h"

ConCreteFactory* ConCreteFactory::m_Instance = NULL;

ConCreteFactory* ConCreteFactory::GetInstance()
{
    if (NULL == m_Instance) {
        m_Instance = new ConCreteFactory();
    }
    return m_Instance;
}

ConCreteFactory::ConCreteFactory()
{

}

UICommonBase*  ConCreteFactory::CreateUICommon(UIC_KIND kind)
{
    switch(kind) {
    case UIC_KIND_PHONE:
        return static_cast<UICommonBase*>(new UICommonPhone());
        break;
    case UIC_KIND_APPSTART:
        break;
    case UIC_KIND_APPS:
        break;
    case UIC_KIND_END:
    default:
       break;
    }
}

