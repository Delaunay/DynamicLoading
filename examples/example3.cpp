/*******************************************************************************
 *
 *      Multiple Object in one DLL
 *      Use a Shared Library to initialize DynamicObject
 *      SharedLibrary Self Memory Management
 *
 ******************************************************************************/

#include <iostream>
#include <string>
#include <DynamicLoading/DynamicObject.h>

#include "ex3_Base.h"

using namespace std;
using namespace DynamicLoading;

//#ifdef __linux__
//#   define name_fix(path, name) "./" + string(path) + "lib" + string(name) + ".so"
//#else
//#   define name_fix(path, name) "./" + string(path) + string(name) + ".dll"
//#endif


int main(int argc, char** argv)
{
    SharedLibrary* sl = new SharedLibrary(name_fix("ex3_plugin1", "plugin/"));

    DynamicUnique<Base1> object1(*sl, "create_obj1", "destroy_obj1");

    delete sl;


    // Shared library was not unloaded
    SharedLibrary sl2 = object1.shared_library();

    DynamicUnique<Base2> object2(sl2, "create_obj2", "destroy_obj2");


    cout << "Plugin 1: " << object1->function1(1) << "\n";
    cout << "Plugin 2: " << object2->function2(1) << "\n";

    return 0;
}
