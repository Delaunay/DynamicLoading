#include <DynamicLoading/Plugin.h>

#include "../ex3_Base.h"

class MyPlugin1 : public Base1
{
public:

    MyPlugin1():
        x(11)
    {}

    ~MyPlugin1() = default;

    int function1(const int& z)
    {
        return x + z;
    }


private:
    int x;

};

class MyPlugin2 : public Base2
{
public:

    MyPlugin2():
        x(11)
    {}

    ~MyPlugin2() = default;

    int function2(const int& z)
    {
        return x * z;
    }


private:
    int x;

};

extern "C"{

    PLUGIN_EXPORT void  destroy_obj1(void* o)  {   delete (MyPlugin1*) o;   }
    PLUGIN_EXPORT void* create_obj1()         {   return new MyPlugin1;  }

    PLUGIN_EXPORT void  destroy_obj2(void* o)  {   delete (MyPlugin2*) o;   }
    PLUGIN_EXPORT void* create_obj2()         {   return new MyPlugin2;  }
}


