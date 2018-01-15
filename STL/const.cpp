#include<iostream>
using namespace std;

bool set(){
	return true;
}

class Base {
public:
	int m_base;
	Base():m_base(10){}
	virtual void one() {cout << "First::one" << endl;}	
	virtual void two() {cout << "First::two" << endl;}	
	virtual void thr() {cout << "First::thr" << endl;}	
};

class First :public Base
{
public:
	virtual void one() {cout << "First::First!" << endl;}	
	virtual void two() {cout << "First::Second" << endl;}	
	virtual void thr() {cout << "First::thirth" << endl;}	
	virtual void four() {cout << "First::four" << endl;}	
	
};

int main() 
{
	typedef void (*Fun)(void);	
	First f;
	int *b = (int*)&f;
	int *c = (int*)(*(int*)&f);
	cout << b << endl;
	cout << c << endl;
	cout << endl;
	Fun pFun = NULL;
	pFun = (Fun)*c;
	pFun();
	Fun  pFun1 = pFun + 1;
	pFun1();
	
	


	//pFun = (Fun)b[0][1];
//	pFun();
//	for(int i = 0; (Fun)(b[0][i]) != NULL; i++ ) {
//		pFun = (Fun)(b[0][i]);
//		pFun();
//		cout << i << endl;
//	}
} 
