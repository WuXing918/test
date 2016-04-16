#include <iostream>
#include "ProxySubject.h"

using namespace std;

int main()
{
    Subject * proxy = new ProxySubject();
    proxy->Request();

    return 0;
}

