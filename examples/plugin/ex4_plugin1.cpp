#include <DynamicLoading/Plugin.h>

#include "../ex4_Base.h"
#include "../ObjType.h"

class MyPlugin : public Base
{
public:

    MyPlugin():
        x(20, 20), y(11, 11)
    {}

    ~MyPlugin() = default;

    ObjType function()
    {
        return ObjType(10, 10);
    }

    ObjType& function_ref()
    {
        return x;
    }

    virtual MyPoints& function_template()
    {
        return y;
    }

    ObjType x;
    MyPoints y;
};

void  destroy_object(void* o)  {   delete (MyPlugin*) o;   }
void* create_object()         {   return new MyPlugin;  }

