#include <stdio.h>

void print(int *a, int lengh) {
	for(int i = 0; i < lengh; i ++ ){
		printf("%d ", a[i]);
	}
	printf("\n");
}

void sort(int *a, int lengh) {
	for (int i = 0; i< 10; i++) {
		for (int j = 0; j < lengh - i -1; j ++) {
			if (a[j] > a[j+1]) {
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		} 
	}
}

void select(int *a , int lengh) {
	for (int i = 0; i< lengh -1; i ++) {
		int min = i;
		for (int j = i+1; j < lengh; j++) {
			if (a[min] > a[j]) {
				min = j;
			}
		}
		if (min != i) {
			int temp = a[i];
			a[i] = a[min];
			a[min] = temp;
		}
	}

}

void insert(int *a , int lengh) {
	for (int i = 1; i < lengh; i ++) {
		// 要插入的数据
		int temp = a[i];
		// 插入的出事位置
		int j = i;
		for ( j; (j >= 0) && a[j-1] > temp; j--) {
			a[j] = a[j-1];
		}
		a[j] = temp;
	}
}

void quick(int *a, int L, int R){
	int i = L;
	int j = R;
	int key = a[i];
	while(i < j) {
		while((key < a[j]) && (i < j)) {
			j--;
		}
		// this location is too easy to understand;
		a[i] = a[j];
		print(a,10);
		while((key > a[i]) && (i < j)) {
			i++;
		}
		a[j] = a[i];
		print(a,10);	
	}
	a[i] = key; 
	printf("-----------------------------\n");
	print(a,10);
	printf("-----------------------------\n");
	// 一次快速排序结束
	quick(a, L, i-1);
	quick(a, j+1, R);
}

int main() {
	int a[10] = {5,7,1,9,2,3,8,6,0,4};
	print(a ,10);
	//sort(a, 10);
	//select(a,10);
	quick(a, 0,9);
	//insert(a,10);
	print(a, 10);

}
