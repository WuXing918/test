#include  <iostream>
using namespace std;

void print(int *a, int length) 
{
	for (int i = 0; i < length; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void sort(int *a, int length)
{
	int j,i;
	// 插入数据的个数，也就是插入次数
	for (i = 1; i< length; i++) {
		int temp = a[i];
		j = i-1; 
		// 从右向前比较插入
		while (j >= 0 && a[j] > temp) {
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = temp;
	}
}



int main() 
{
	int a[] = {9,2,5,7,8,1,0,4,3,6};
	print(a, 10);
	sort(a, 10);
	print(a, 10);
}
