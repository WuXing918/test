#ifndef SUBJECT_H
#define SUBJECT_H

#define NULL 0


class Subject
{
public:
    Subject();
    virtual void Request() = 0;
};

#endif // SUBJECT_H
