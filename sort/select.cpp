#include <stream>

void print( int* const &a, int length) 
{
	for (int i = 0; i < length; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void sort(int* a, int length) 
{
	for(int i = 0; i< length; ++i) {
		for(int j = i+1; j < length; ++j) {
			if(a[i] > a[j]) {
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
		print(a,10);
	}
}


int main() 
{
	int a[10] = {5,1,3,0,4,9,2,7,6,8};
	int 
}
