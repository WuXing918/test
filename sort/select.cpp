#include <iostream>
using namespace std; 
void print( int* const &a, int length) 
{
	for (int i = 0; i < length; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void select_sort(int a[], int length) 
{
	for(int i = 0; i< length; i++) {
		int min = i;
		for(int j= i+1; j < length; j++) {
			if(a[min] > a[j]) {
				min = j;
			}
		}
		if(min != i) {
			int temp = a[i];
			a[i] = a[min];	
			a[min] = temp;
		}
		print(a, 10);
	} 
}
// 我写的和  select 排序基本一致，只是每次都换，而select 是只换一次，一次排序记住最小的下标，排序完成后在进行互换。
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
	print(a, 10);
	cout << "----------start--------------" << endl;
	select_sort(a, 10);
	cout << "-----------end-------------" << endl;
	int b[10] = {5,1,3,0,4,9,2,7,6,8};
	cout << "---------start---------------" << endl;
	sort(b, 10);
	cout << "----------end----------------" << endl;
	print(b, 10);
	
}
