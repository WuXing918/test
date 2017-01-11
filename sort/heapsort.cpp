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
    int nchild = a[2*i];
    // 存储的当前树中的临时最大值
    int temp;
    // 存储当前书中的临时最大之的位置
    int locate;
    while(2*i < length) {
        // 1. 判断出左右子树的大小存储在temp中        
        if ((2*i+1) < length) { 
            // 判断有右子树       
            if (a[2*i] > a[2*i+1]) {
                locate = 2*i;
                temp = a[2*i];            
            }
            else {
                locate = 2*i+1;
                temp = a[2*i+1];            
            }
        }
        else {
            // 判断没有右子树
            locate = 2*i;
            temp = a[i];
        }
        
        // 判断子节点与父节点大小
        if (a[i] >= temp) {
            // 该树已经是大根堆模式            
            break;        
        }
        else {
            int swap = a[i];
            a[i] = temp;
            a[locate] = swap;
            temp = swap;
            i = locate;
        }
    }
}

void heapAjust() {

}









int main () {
	int a[] = {7,0,2,6,1,8,3,9,4,5};
	print(a, sizeof(a)/sizeof(a[0]));
	// 创建堆的过从程
    int length = sizeof(a)/sizeof(a[0]);
    for (int i = length/2; i > 0; i--) {
        // 这个i和a[]下标是有区别的 
        heapCreate(a, i, length);
    } 
    print(a, sizeof(a)/sizeof(a[0])); 
}

