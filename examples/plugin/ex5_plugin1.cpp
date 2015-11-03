#include <DynamicLoading/Plugin.h>

#include "../ex5_Base.h"

class MyPlugin : public Base
{
public:

    MyPlugin() = default;

    virtual ObjType& compute_stuff(Matrix& x)
    {
        mat_struct.x = x;

        return mat_struct;
    }
};


void  destroy_object(void* o)  {   delete (MyPlugin*) o;   }
void* create_object()         {   return new MyPlugin;  }


#if 0
#include <DynamicLoading/Plugin.h>

#include "../ex5_Base.h"

#define DEFINE_ATTRIBUTE(x, y, z)
#define DEFINE_METHOD(rtype, name, ...)

class MyPlugin
{
public:

    MyPlugin() = default;
    ~MyPlugin() = default;

    DEFINE_ATTRIBUTE(int, my_attribute, 10);
    DEFINE_METHOD(int, my_method, int, double);
};

void  destroy_object(void* o)  {   delete (MyPlugin*) o;   }
void* create_object()         {   return new MyPlugin;  }

extern "C"{
    int* my_attribute(){
        static int attr = 10;
        return attr;
    }

    int my_method(void* o, int i, double d){
        return o->my_method(i, d);
    }
}
#endif
