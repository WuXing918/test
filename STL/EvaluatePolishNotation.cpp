#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int simpleEvaluate(int ope1, int ope2, string ope) {
	if(ope == "+"){
		return (ope1 + ope2);
	}
	else if( "-" == ope) {
		return (ope1 - ope2);
	}
	else if ("*" == ope){
		return (ope1 * ope2);
	}
	else if("/" == ope) {
	//	return (ope / ope2);
	}
	else {
	}
}

int strToInt(string str) 
{
	cout << "strToInt:" << str << endl;
	int count = 0;
	for(int i = 0; i < str.length(); i++) {
		count = count*10 + (str[i]-'0');
	}
	return count;
}

int Evaluate(vector<string>& str) 
{
	stack<int> stk;
	for (int i = 0; i< str.size(); i++) {
		if (str[i] == "+" || str[i] == "-" || str[i] == "*" || str[i] == "/") {
			int temp2 = stk.top();
			stk.pop();
			int temp1 = stk.top();
			stk.pop();
			int temp3  = simpleEvaluate(temp1, temp2, str[i]);
			cout << temp3 << endl;
			stk.push(temp3);
		}
		else {
	    	stk.push(strToInt(str[i]));
		}
	}
	return stk.top();

}

void print(const vector<string>& str) 
{
	cout << str.size() << endl;
	for(int i = 0; i< str.size(); i++) {
		cout << str[i] << " ";
	}
	cout << endl;
}

int main() 
{
	vector<string> str;
	str.push_back("12");
	str.push_back("12");
	str.push_back("+");
	str.push_back("2");
	str.push_back("*");
	str.push_back("5");
	str.push_back("*");
	print(str);	
	cout << Evaluate(str) << endl;;
	
	cout <<"++++++++++++++++++" << endl;
	string temp("102");
	cout << "-----------------" <<endl;
	cout << strToInt(temp) << endl;
		
}
