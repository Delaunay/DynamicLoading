// override defaults :plugin side
#define DYN_CREATE_OBJ create_plugin
#define DYN_DESTROY_OBJ destroy_plugin

#include <DynamicLoading/Plugin.h>

#include "../ex1_Base.h"

class MyPlugin : public Base
{
public:

    MyPlugin():
        x(11)
    {}

    ~MyPlugin() = default;

    int function(const int& z)
    {
        return x * z;
    }


private:
    int x;

};

void destroy_plugin(void* o)  {   delete (MyPlugin*) o;   }
void* create_plugin()         {   return new MyPlugin;  }


