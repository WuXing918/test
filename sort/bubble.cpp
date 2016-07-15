#include <iostream>
using namespace std;

void print(int* a, int length)
{
	for(int i = 0; i < length; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void bubble_sort(int a[], int n)
{
    int i, j, temp;
    for (j = 0; j < n - 1; j++) {
        for (i = 0; i < n - 1 - j; i++) {
            if(a[i] > a[i + 1])
            {
                temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
            }
        }
	print(a, 10);
	}             
}

int main() 
{
	int a[10] = {9,6,8,1,3,5,4,0,7,2};
	print(a, 10);
	cout << "--------------------" << endl;
	bubble_sort(a, 10);
	cout << "--------------------" << endl;
	print(a, 10);
}
