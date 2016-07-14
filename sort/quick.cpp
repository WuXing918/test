#include <iostream>
using namespace std;
void print(int* a) 
{
	for (int i = 0; i< 10; i ++) {
		cout << a[i] << " ";
	}
	cout << endl;	
}

void sort(int *a, int L, int R)
{
	if (L >= R) {
		return ;
	} 
	int i = L;
	int j = R;
	// 一次快排是将 a[L] 放在左边都比它小，右边都比它大的地方。
	// 主要逻辑是查找这个位置，找到以后将该数据 a[L]放在该位置。
	int key = a[i];
	
	cout << "L = " << L << " R = " << R << " Key = "<< key << endl;
	cout << "i = " << i << " J = " << j << " Key = "<< key << endl;
	// 左边界先加还是有边界先减，取决于key值目前在左边界还是在有边界，如果在左边，那就采取右边先减，否则左边先加。
	// 由于我们在一次排序之前，采取左边界为key值，所以先采取右边界先减的算法。
	while(i < j) {
		while((key <= a[j]) && (i < j)) {
			j--;
		}
		a[i] = a[j];
		while((key >= a[i]) && (i < j)) {
			i++;
		}
		a[j] = a[i];
	}	
	// 找到了该位置，我们将key值放在该位置上。
	a[i] = key;
	cout << "a[i] = " << i << endl;
	print(a);
	
	// 递归调用排序 先左后右
	sort(a, L, i-1);
	cout << "right" << endl;
	sort(a, i+1, R);
}
/*
	快速排序 从左从右开始排序有我们自己决定。

*/


int main() 
{
	int a[] = {5,9,1,3,2,8,4,7,6,0};
	print(a);
	cout << "----------------------" << endl;
	sort(a, 0,9);
	cout << "----------------------" << endl;	
	print(a);
}

