#include <iostream>
#include "Singleton.h"
using namespace std;

int main() 
{
	Singleton::GetInstance()->print();
}
