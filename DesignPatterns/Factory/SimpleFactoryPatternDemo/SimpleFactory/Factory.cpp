#include "Factory.h"
#include "ConCreteFactory.h"

Factory::Factory()
{

}

Factory::~Factory() 
{

}

UICommonBase* Factory::CreateUICommon(UIC_KIND kind)
{
    return ConCreteFactory::GetInstance()->CreateUICommon(kind);
}
