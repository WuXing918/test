#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>

class Component
{
protected:
    std::string name;
public:
    Component(std::string name)
        :name(name)
    {   }
    virtual void AddComponent(Component *component) {   }
    virtual void RemoveComponent(Component *component)  {   }
    virtual void GetChild(int depth)    { }
};

#endif // COMPONENT_H
