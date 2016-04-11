#ifndef COMPOSITE_H
#define COMPOSITE_H
#include <list>
#include "Component.h"
#include <iostream>
class Composite:public Component
{
private:
    std::list<Component*> _componets;

public:
    Composite(std::string name)
        :Component(name)
    { }
    void AddComponent(Component *component)
    {
        _componets.push_back(component);
    }
    void RemoveComponent(Component *component)
    {
        _componets.remove(component);
    }
    void GetChild(int depth)
    {
        std::string tmpstring (depth, '-');
        std::cout<<tmpstring<<name<<std::endl;
        std::list<Component*>::iterator iter = _componets.begin();
        for(; iter != _componets.end(); iter++)
        {
            (*iter)->GetChild(depth + 2);
        }
    }
};


#endif // COMPOSITE_H
