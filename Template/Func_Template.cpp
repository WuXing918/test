/*C++ 模板
模板是C++支持参数多态化的一个工具，使用模板可以使用户为类或者函数声明一种一般模式，使得类中的某些数据成员，或者成员函数的参数，返回值可以取得任意类型。

通常有两种形式：
	模板函数： 函数参数不同的函数。
	类模板  ： 数据成员和成员函数类型不同的类。
使用模板的目的就是能够让程序员编写出与类型无关的代码。

函数模板的格式：
	// 备注typename 和class关键子可以替换，没有什么区别。
	template <typename 形参名， typename 形参名，……>
	返回值类型 函数名称(参数列表) 
	{
		函数体；
	}

类模板的格式：
	template <typename 形参名， typename 形参名，……>
	class 类名
	{
		……
	}；
*/
	



#include <stdio.h>

	
template <typename T>
T add(T numleft, T numright) 
{
	return numleft + numright; 
}

int main ()
{
	printf("left + right = %d\n", add(5,10));
	printf("left + right = %1f\n", add(5.1,10.4));
}

