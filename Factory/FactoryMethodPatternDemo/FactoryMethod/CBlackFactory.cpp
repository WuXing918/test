#include "CBlackFactory.h"
#include "CBlackHuman.h"

CBlackFactory::CBlackFactory()
{

}

CBlackFactory::~CBlackFactory()
{

}

IHuman* CBlackFactory::CreateHuman()
{
    return new CBlackHuman();
}

