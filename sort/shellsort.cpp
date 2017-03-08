#include <iostream>
using namespace std;

void print(int a[], int length) {
	for (int i = 0; i < length; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void shellsort(int a[], int length) {
    

}

int main() {
    int a[] = {7,0,2,6,1,8,3,9,4,5};
     int length = sizeof(a)/sizeof(a[0]);
    print(a, length);

    shellsort(a, length);
}
