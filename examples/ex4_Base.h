#ifndef EX4_BASE_HEADER
#define EX4_BASE_HEADER

#include <DynamicLoading/Plugin.h>
#include "ObjType.h"

typedef Point<double, double> MyPoints;

class Base
{
public:

    Base() = default;

    virtual ~Base() = default;

    virtual ObjType function() = 0;

    virtual ObjType& function_ref() = 0;

    virtual MyPoints& function_template() = 0;

};

#endif
