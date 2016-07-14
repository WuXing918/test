#include <iostream>
using namespace std;

void print(int* a, int length)
{
	for(int i = 0; i < length; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void sort(int *a, int length) 
{
}

int main() 
{
	int a[10] = {9,6,8,1,3,5,4,0,7,2};
	print(a, 10);
	sort(a, 10);
}
