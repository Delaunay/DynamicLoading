#ifndef CXXMODULE_DLLOADER_HEADER
#define CXXMODULE_DLLOADER_HEADER

#include <memory>
#include <string>
#include <cassert>

// Error Handling
#include "ErrorPolicy.h"

#ifdef __linux__
#   include <dlfcn.h>
#else
#   include <windows.h>
#   define RTLD_LAZY 1
#   define dlsym(dll, function_name) GetProcAddress(dll, function_name)
#endif

namespace DynamicLoading{

// "./" make the prog seek the dll in the exe folder
inline std::string name_fix(const std::string& name, const std::string& path = "./")
{
#ifdef __linux__
    return path + "lib" + name + ".so";
#elif __MINGW32__
    return path + "lib" + name + ".dll";
#else
    return path + name + ".dll";
#endif
}

/*!
 * This class load a SharedLibrary (dll) and enable you to retrieve
 * its functions. Behavior may change across operating system (see dlopen
 * and LoadLibraryA for more details)
 *
 * Usage
 * -----
 *
 *      typedef int (*callback)(int, int);
 *
 *      SharedLibrary my_sl("./libSharedLib.so");
 *
 *      callback function = my_sl.get_function<callback>("my_function");
 *
 *      function(1, 2);
 *
 *
 * Implementation
 * --------------
 *
 *  SharedLibrary is a reference counting pointer. The library is unloaded when
 *  it is not used anymore
 *
 */
class SharedLibrary
{
public:
#ifdef __linux__
    typedef void* LibraryHandle;
#else
    typedef HINSTANCE LibraryHandle;
#endif

    typedef void (*deleter)(LibraryHandle);
    typedef std::shared_ptr<LibraryHandle> PtrLibrary;
    typedef std::size_t size_type;

    SharedLibrary(const SharedLibrary& lib);

    SharedLibrary(const std::string& name, int flag = RTLD_LAZY);

    SharedLibrary& operator= (const SharedLibrary& lib);

    ~SharedLibrary() noexcept;

    inline operator bool() const    {   return _module != 0; }

    template<typename T>
    T get_function(const std::string& name) const
    {
        T t = reinterpret_cast<T>(dlsym(_module, name.c_str()));   // reinterpret_cast of nullptr works
        THROW(t == 0, std::runtime_error, "Unknown Symbol");       //
        return t;
    }

    template<typename T>
    T get_function_nocheck(const std::string& name) const
    {
        return reinterpret_cast<T>(dlsym(_module, name.c_str()));
    }

    const char* error() const;

private:

    void close_module();    // user must not use that function

private:

    size_type*    _ref_count;
    LibraryHandle _module;
};
}
// Remove Macro
#ifndef __linux__
#   undef RTLD_LAZY
#   undef dlsym
#endif
#endif
