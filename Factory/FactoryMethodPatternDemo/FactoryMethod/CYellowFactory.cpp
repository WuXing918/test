#include "CYellowFactory.h"
#include "CYellowHuman.h"
#include <iostream>
using namespace std;

CYellowFactory::CYellowFactory()
{

}

CYellowFactory::~CYellowFactory()
{

}

IHuman* CYellowFactory::CreateHuman()
{
    return new CYellowHuman();
}

