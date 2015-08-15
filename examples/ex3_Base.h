#ifndef EX3_BASE_HEADER
#define EX3_BASE_HEADER

class Base1
{
public:

    Base1() = default;

    virtual ~Base1() = default;

    virtual int function1(const int& z)=  0;

};

class Base2
{
public:

    Base2() = default;

    virtual ~Base2() = default;

    virtual int function2(const int& z)=  0;

};

#endif
