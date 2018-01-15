#include <iostream>
#include <stack>
#include <string.h>
using namespace std;
bool matchparentheses(char* str) 
{
	stack<char> stk;
	int length = strlen(str);
	cout << length << endl;
	for (int i = 0; i < length; i++) {
		if ('(' == str[i] || '[' == str[i] || '{' == str[i]) {
			stk.push(str[i]);
		}
		else if (')' == str[i] || ']'== str[i] || '}' == str[i]){
			switch (str[i]) {
			case ')':
			{
				if (!stk.empty()){
					if (stk.top() == '(') { stk.pop(); }
					else {  return false; }
				}
				else {
					return false;
				}
				break;
			}
			case ']': 
			{
				if (!stk.empty()) {
					if (stk.top() == '[') {
						stk.pop();
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
				break;
			}
			case '}':
			{
				if (!stk.empty()) {
					if (stk.top() == '{') {
						stk.pop();
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
				break;
			}
			defalt:
				break;
			}
		}
		else {

		}
	}
	cout << "遍历结束" << endl;
	if (stk.empty()) {
		cout << "已经为空栈" << endl;
		return true;
	}
	cout << "非空栈" << endl;
	
	return false;
}

int main() {
	char pstr[] = "((wu(xing(wu){x[i]}())))";

  	cout <<  matchparentheses(pstr) << endl;
}
