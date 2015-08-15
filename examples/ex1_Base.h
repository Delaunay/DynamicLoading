#ifndef EX1_BASE_HEADER
#define EX1_BASE_HEADER

class Base
{
public:

    Base() = default;

    virtual ~Base() = default;

    virtual int function(const int& z)=  0;

};

#endif
