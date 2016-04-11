#ifndef CONCRETESUBJECT_H
#define CONCRETESUBJECT_H
#include "Subject.h"
#include "Observer.h"
class ConcreteSubject : public Subject
{
public:
     /// 注册观察者
     void Attach(Observer *pObserver);
     /// 注销观察者
     void Detach(Observer *pObserver);
     /// 通知(广播到每一个注册的观察者)
          void Notify();
    /// 主题状态设置
     void SetState(int state);

private:
     /// Observer 集合
     std::list<Observer *> m_ObserverList;
     /// 主题状态
     int m_iState;
};


#endif // CONCRETESUBJECT_H
