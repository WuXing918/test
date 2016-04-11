#include "CWhiteFactory.h"
#include "CWhiteHuman.h"

CWhiteFactory::CWhiteFactory()
{

}

CWhiteFactory::~CWhiteFactory()
{

}

IHuman* CWhiteFactory::CreateHuman()
{
    return new CWhiteHuman();
}
