/*******************************************************************************
 *
 *      Simpliest Example of DynamicObject Usage
 *
 ******************************************************************************/

#include <iostream>
#include <string>
#include <DynamicLoading/DynamicObject.h>

#include "ex1_Base.h"

using namespace std;
using namespace DynamicLoading;

#ifdef __linux__
#   define name_fix(path, name) "./" + string(path) + "lib" + string(name) + ".so"
#else
#   define name_fix(path, name) "./" + string(path) + string(name) + ".dll"
#endif


int main(int argc, char** argv)
{
    DynamicObject<Base> object1(name_fix("plugin/", "ex1_plugin1"));

    cout << "Plugin 1: " << object1->function(1) << "\n";

    DynamicObject<Base> object2(name_fix("plugin/", "ex1_plugin2"));

    cout << "Plugin 2: " << object2->function(1) << "\n";

    return 0;
}
