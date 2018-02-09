#include <iostream>
#include <string.h>
using namespace std;
/*
	一个空类默认提供几个函数，默认空参构造函数，拷贝构造函数，赋值函数，析构函数，取址运算符，取址运算符const。
	注意：
		这些函数只有当你需要使用的时候，编译器才会定义。
		拷贝构造和赋值函数，只是浅拷贝，和浅赋值。
		所有这些函数都是inline，public 函数。
*/
class String 
{
public:
	//普通构造函数，包含空参构造和有参构造。 
	String(const char* data = NULL);
	// 拷贝构造函数参数为什么一定是引用？, 避免无限递归调用拷贝构造函数。
	String(const String& str);
//运算符重载,有些可以重载为成员函数，有些只能重载为友元函数。
	// 可以不加&修饰,加&修饰避免函数参数初始化开销.
	String& operator=(const String& str);
	char operator[](const int nPos);
// 友元函数
	friend ostream& operator<< (ostream&, const String&);
	friend istream& operator>> (istream&, String&);
	virtual ~String();
	void print();	
/* 
 * 对于const 关键字修饰函数时，声明中和实现中都需要出现。
 */
private:
	char* m_data;
};

String::String(const char* data) 
{
	cout << "String(const char* data)" << endl;
	// 空参构造的的情况，保证对象的唯一性，分配一个字节内存。
	if (NULL == data) {
		m_data = new char[1];
		*m_data = '\0';
	}
	else {
		int length = strlen(data);
		m_data = new char[length+1];
		strcpy(m_data,data);
	}
}

// 拷贝构造函数，如果有指针等，需要注意浅拷贝问题，防止两个类指向同意内存地址，释放时造成内存丢失。
String::String(const String& str) 
{
	// 类的成员函数可以访问该类的所有对象的所有成员，当然也包括似有成员。
	cout << "String(const String& str)" << endl;
	int length = strlen(str.m_data);
	m_data = new char[length+1];
	strcpy(m_data, str.m_data);
}

String& String::operator =(const String& str)
{
	cout << "String::operator =(const String& str)" << endl;
    // 判断自赋值
	if (this == &str) {
		cout << "自赋值" << endl;
		return *this;
	}
	// 销毁原有内存。
	delete [] m_data;
	int length = strlen(str.m_data);
	// 必须从新申请内存保存内容。
	m_data = new char[length+1];
    //重新赋值
	strcpy(m_data, str.m_data);
	return *this;	
}

char String::operator[](const int nPos)
{
	int temp = strlen(m_data);
	
	if (nPos >= 0 || nPos <= temp) {
		return m_data[nPos];
	}
	return -1;
}

ostream& operator<< (ostream& out, const String& s)
{
	out << s.m_data;
	return out;
}

istream& operator>> (istream& in, String& s)
{
	in >> s.m_data;
	return in;
}

String::~String() 
{
	cout << "String::~String()" << endl;
	delete [] m_data;
	m_data = NULL;
}

void String::print() {
	cout << m_data << endl;
}

int main() 
{
	String a;
	a.print();
	String b("wuxing");
	b.print();
	String c(b);
	c.print();
	String d = c;
	d.print();	
	d = c;
	d.print();
	cout << c[2] << endl;
	cout << c << endl;
	cin >> c;
	cout << c << endl;
}

