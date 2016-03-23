#ifndef SINGLETON_H
#define SINGLETON_H

class Singleton 
{
public:
    static Singleton* GetInstance();

    static void DestroyInstance(); 
   
    void print();    
private:
    Singleton();
    ~Singleton();
    
private:
    static Singleton* m_Instance;
private:
    
};

#endif
