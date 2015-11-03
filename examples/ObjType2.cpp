#include "ObjType2.h"


ObjType::ObjType(int x_, int y_)
{
    x = Matrix::Zero(2, 2);
    y = Matrix::Zero(2, 2);

    x.fill(x_);
    y.fill(y_);
}

std::ostream& operator<< (std::ostream& os, const ObjType& t)
{
    Eigen::IOFormat fmt;

    os << "(" << t.x.format(fmt) << "x" << t.y.format(fmt) << ")";
    return os;
}
