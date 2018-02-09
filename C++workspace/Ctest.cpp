#include <iostream>
using namespace std;
class Wuxing
{
public:
	Wuxing(){}
	~Wuxing(){}
	Wuxing* getwuxing()
	{
		if(wuxing == NULL) {
			wuxing = new Wuxing();
		}
		return wuxing;	
	}
	
	void print()
	{
		cout << "wuxing" << endl;
		cout << wuxing << endl;
	}
private:
	Wuxing *wuxing;
};

int main()
{
	
	Wuxing *xing;
	cout << xing << sizeof(*xing) <<endl;
	xing->print();
}

