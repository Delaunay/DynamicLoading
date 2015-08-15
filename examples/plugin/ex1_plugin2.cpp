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

void destroy_object(void* o)  {   delete (MyPlugin*) o;   }
void* create_object()         {   return new MyPlugin;  }


