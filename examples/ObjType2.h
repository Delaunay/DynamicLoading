#ifndef EX5_OBJ_HEADER
#define EX5_OBJ_HEADER

#include "enum.h"
#include <ostream>

struct ObjType
{
public:

    ObjType(int x, int y);

    Matrix x;
    Matrix y;
};

std::ostream& operator<< (std::ostream& os, const ObjType&);

#endif
