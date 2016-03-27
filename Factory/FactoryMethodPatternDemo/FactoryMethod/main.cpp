#include <iostream>
#include "IHuman.h"
#include "IHumanFactory.h"
#include "CBlackFactory.h"
#include "CYellowFactory.h"
#include "CWhiteFactory.h"
#include "IHuman.h"
#include "CBlackHuman.h"
using namespace std;

int main()
{
    IHumanFactory* humanfactory1 = new CBlackFactory();
    IHuman* human1 = humanfactory1->CreateHuman();
    human1->laugh();
    cout << "--------------------------------------------------" << endl;

    IHumanFactory* humanfactory2 = new CWhiteFactory();
    IHuman* human2 = humanfactory2->CreateHuman();
    human2->laugh();
    cout << "--------------------------------------------------" << endl;

    IHumanFactory* humanfactory3 = new CYellowFactory();
    IHuman* human3 = humanfactory3->CreateHuman();
    human3->laugh();
    cout << "--------------------------------------------------" << endl;

    return 0;
}

