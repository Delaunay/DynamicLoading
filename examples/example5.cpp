/*******************************************************************************
 *
 *      Idea
 *
 ******************************************************************************/

#include <iostream>
#include <string>
#include <DynamicLoading/DynamicObject.h>

#include "ex5_Base.h"

using namespace std;
using namespace DynamicLoading;

//#ifdef __linux__
//#   define name_fix(path, name) "./" + string(path) + "lib" + string(name) + ".so"
//#else
//#   define name_fix(path, name) "./" + string(path) + string(name) + ".dll"
//#endif


int main(int argc, char** argv)
{
    DynamicObject<Base> object(name_fix("ex5_plugin1", "plugin/"));

    Matrix x(1, 1);
    x.fill(10);

    cout << object->mat_struct << "\n";
    cout << object->compute_stuff(x) << "\n";

    return 0;
}
