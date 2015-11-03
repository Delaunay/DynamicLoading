#ifndef EX5_BASE_HEADER
#define EX5_BASE_HEADER

#include "ObjType2.h"

class Base
{
public:
    Base():
        mat_struct(10, 10)
    {}


    virtual ObjType& compute_stuff(Matrix& x)
    {
        return mat_struct;
    }

    ObjType mat_struct;
};


#endif
