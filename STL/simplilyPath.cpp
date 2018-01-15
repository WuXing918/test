#include <iostream>
#include <string>
#include <stack>
using namespace std;
char* SimplilyPath(char* str)
{
	cout << str <<endl;
	stack<char> stk;
	string ss;
	int i = 0;
	while(*str != '\0') {
		// 当前是'/' 的情况
		cout << "当前是'/' 的情况" << endl;
		if (*str == '/') {
			if (stk.top() == '/') {
				// '/' 处理一次
				cout << "'/' 处理一次" << endl;
				continue;
			}
			else if (stk.top() == '.'){
				cout << "stk.top() == '.'" << endl;
				stk.pop();
			 	if (stk.top() == '/') {
					continue;
				}
				//else if(stk.top() == '.'){
				//	while (stk.top() != '/') {
				//		stk.pop();
				//	}
				//}
			}
			else {

			}
		}
		// 但前不是 '/'的情况
		else {
			cout << "当前不是'/' 的情况" << endl;
			stk.push(*str);
		}
		str++;
	}
	
	while(!stk.empty()){
		
	}
	return str;
}
int main ()
{
	char str[] = "17Cy_Pro/17Cy_L2_200B/packages/../../L_master/../../.ssh/";
	SimplilyPath(str);
}
