#ifndef EX4_OBJ_HEADER
#define EX4_OBJ_HEADER

#include <ostream>

template<typename T1, typename T2>
struct Point
{
    Point(T1 x, T2 y):
        x(x), y(y)
    {}

    T1 x;
    T2 y;
};

template<typename T1, typename T2>
std::ostream& operator<< (std::ostream& os, const Point<T1, T2>& t)
{
    os << "(" << t.x << "x" << t.y << ")";
    return os;
}

struct ObjType
{
public:

    ObjType(int x, int y);

    int x;
    int y;

};

std::ostream& operator<< (std::ostream& os, const ObjType&);

#endif
