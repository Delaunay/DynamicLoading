/*******************************************************************************
 *
 *      Use of extern non POD types
 *
 ******************************************************************************/

#include <iostream>
#include <string>
#include <DynamicLoading/DynamicObject.h>

#include "ex4_Base.h"

using namespace std;
using namespace DynamicLoading;

#ifdef __linux__
#   define name_fix(path, name) "./" + path + "lib" + name + ".so"
#else
#   define name_fix(path, name) "./" + path + name + ".dll"
#endif



int main(int argc, char** argv)
{
    DynamicObject<Base> object(name_fix(string("plugin/"),
                                        string("ex4_plugin1")));

    cout << "     Obj : " << object->function() << "\n";

    cout << "     Ref : " << object->function_ref() << "\n";

    cout << "template : " << object->function_template() << "\n";

    return 0;
}
