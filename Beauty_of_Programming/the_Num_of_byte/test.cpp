/*
1. switch 解决，2.查表
*/
#include <iostream>
using namespace std;
int countTable[] = {0,1,1,2,1,2,2,1}; 
// abs(); 取绝对值函数
// 数的二进制中是否有1 看他除除以2的余数
int couByte1(int num) {
	int count = 0;
	while(num) {
		// 数对2求余，该数据不会变化。
		count += num%2;
		num = num/2;
	}
	return count;	
}
//操作数的二进制位
int couByte2(int num) {
	int count = 0;
	while (num) {
		count += num & 0X01;
		num >>= 1;
	}
	return count;
}
// 
int couByte3(int num) {
	int count = 0;
	while (num) {
		count ++;
		num &=(num -1);
	}
	return count;
}
// 定义一维标查表法
int couByte4(int num) {
	return countTable[num];
}
int main() 
{
	int num = 0;
	cin >> num;
	cout << "num = " << num << endl;
	cout << "couByte1(num) :" << couByte1(num) << endl;
	cout << "couByte2(num) :" << couByte2(num) << endl;
	cout << "couByte3(num) :" << couByte3(num) << endl;
}
