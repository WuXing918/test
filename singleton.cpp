#include <cstdio>

class Singleton 
{
public:
	static Singleton* getinstance();
private:
	Singleton();
	static Singleton *ptSingleton;
};

Singleton::Singleton()
{	
}

Singleton* Singleton::getinstance()
{
	if(ptSingleton = NULL)
	{
		ptSingleton = new Singleton;
	}
	return ptSingleton;
}

Singleton* Singleton::ptSingleton = NULL;


int main()
{
	Singleton *ptr = Singleton::getinstance();
	if(ptr != NULL)
	{
		printf("sucess!\n");
	}else{
		printf("%psucess!\n",ptr);	
	}
	return 0;		
}
