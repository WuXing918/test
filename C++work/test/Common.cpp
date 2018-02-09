#ifndef COMMON_H
#define COMMON_H
#include <iostream>
using namespace std;
class Common :public CommonBase 
{
pubulic:
	virtual void setValue(){
		cout << "Common" << endl;
	}

};

#endif

