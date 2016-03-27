#include "Factory.h"
#include "UICommonPhone.h"
#include "factory_global.h"
int main()
{
    Factory* factory = new Factory();

    UICommonPhone* phone = static_cast<UICommonPhone*>(factory->CreateUICommon(UIC_KIND_PHONE));
    phone->print();

}
