/*******************************************************************************
 *
 *      Overides function name defaults
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
    // First method
    //-------------

    // override default
    create_function_name() = "create";
    destroy_function_name() = "destroy";

    DynamicObject<Base> object1(name_fix("plugin/", "ex2_plugin1"));

    cout << "Plugin 1: " << object1->function(1) << "\n";

    // Second Method
    //--------------

    // specify function name
    DynamicObject<Base> object2(name_fix("plugin/", "ex2_plugin2"),
                                "create_plugin", "destroy_plugin");

    cout << "Plugin 2: " << object2->function(1) << "\n";

    return 0;
}
