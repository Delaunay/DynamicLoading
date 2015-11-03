#include "ObjType.h"

ObjType::ObjType(int x, int y):
    x(x), y(y)
{}

std::ostream& operator<< (std::ostream& os, const ObjType& t)
{
    os << "(" << t.x << "x" << t.y << ")";
    return os;
}

