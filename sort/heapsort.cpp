#include <iostream>
using namespace std;

void print(int a[], int length) {
	for (int i = 0; i < length; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

// 我写的好像没有判断根节点
void heapCreate(int a[], int i, int length) {
    //当前父结点的左子树
    int Lchild = 2*i+1;
    int rchild = 2*i+2;    
    // 存储的当前堆中的临时最大值
    // 存储当前堆中的临时最大之的位置
    int locate;
    while(2*i+1 < length) {
        // 1. 判断出左右子树的大小存储在temp中        
        if ((2*i+2) < length) { 
            // 判断有右子树       
            if (a[2*i+1] > a[2*i+2]) {
                locate = 2*i+1;        
            }
            else {
                locate = 2*i+2;
            }
        }
        else {
            // 判断没有右子树
            locate = 2*i+1;
        }
        
        // 判断子节点与父节点大小
        if (a[i] >= a[locate]) {
            // 该树已经是大根堆模式            
            break;        
        }
        else {
            int swap = a[i];
            a[i] = a[locate];
            a[locate] = swap;
            i = locate;
        }
    }
}

void heapSort(int a[], int length) {
    // 创建堆的过从程
    for (int i = length/2-1; i >= 0; i--) {
        // 这个i和a[]下标是没有区别的 
        heapCreate(a, i, length);
    }     
    for (int j = length-1; j >= 0; j--)  {
        int temp = a[j];
        a[j] = a[0];
        a[0] = temp;
        heapCreate(a, 0, j);
    }    
}


int main () {
    
	int a[] = {7,0,2,6,1,8,3,9,4,5};

    int length = sizeof(a)/sizeof(a[0]);
    print(a, length);
    heapSort(a, length);
    print(a, length);




 
    
}

