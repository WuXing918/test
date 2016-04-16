#ifndef SUBJECT_H
#define SUBJECT_H


class Subject
{
public:
    Subject();
    ~Subject();
    virtual void Attach();
    virtual void Detach();
    virtual void Notify();
    virtual void SetPrice();
    virtual void SetNum();
};

#endif // SUBJECT_H
