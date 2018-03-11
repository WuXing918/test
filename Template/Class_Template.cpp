#include <iostream> 
using namespace std;
	
template <class T>
class Math  {
public:
	T add(T num1, T num2)
	{
		return num1 + num2;
	}
	T jian(T num1, T num2)
	{
		return num1 - num2;
	}	
};

int main () {
	Math<int> math;
	cout << "add(1,2) = " << math.add(1,2) << endl;
	cout << "jian(2,1) = " << math.jian(2,1) << endl;
	Math<float> math1;
	cout << "add(1.1,2.2) = " << math1.add(1.1,2.2) << endl;
	cout << "jian(2.2,1.1) = " << math1.jian(2.2,1.1) << endl;
}
