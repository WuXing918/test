#ifndef LEAF_H
#define LEAF_H
#include "Component.h"
#include <iostream>
class Leaf: public Component
{
public:
    Leaf(std::string name)
        :Component(name)
    {   }
    void AddComponent(Component *component)
    {
        std::cout<<"Leaf can't add component"<<std::endl;
    }
    void RemoveComponent(Component *component)
    {
        std::cout<<"Leaf can't remove component"<<std::endl;
    }
    void GetChild(int depth)
    {
        std::string _tmpstring(depth, '-');
        std::cout<<_tmpstring<<name<<std::endl;
    }
};

#endif // LEAF_H
