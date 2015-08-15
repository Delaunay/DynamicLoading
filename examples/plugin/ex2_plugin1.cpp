// override defaults :plugin side
#define DYN_CREATE_OBJ create
#define DYN_DESTROY_OBJ destroy

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
        return x + z;
    }


private:
    int x;

};

void destroy(void* o)  {   delete (MyPlugin*) o;   }
void* create()         {   return new MyPlugin;  }


