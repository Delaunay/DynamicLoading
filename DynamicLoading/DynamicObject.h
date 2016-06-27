#ifndef CXXMODULE_DYNMOD_HEADER
#define CXXMODULE_DYNMOD_HEADER

#include "SharedLibrary.h"
//#include <functional>

namespace DynamicLoading{

// default creator/destructor function name
inline std::string& create_function_name()
{
    static std::string create = "create_object";
    return create;
}

inline std::string& destroy_function_name()
{
    static std::string destroy = "destroy_object";
    return destroy;
}

namespace internal{
template<typename T>
struct fun{
  typedef T* (*create)();
  typedef void (*destroy)(T*);
};

template<typename T>
struct Deleter
{
    typedef typename internal::fun<T>::destroy destroy_type;

    Deleter() {}

    Deleter(destroy_type d):
        destroy(d)
    {}

    void operator () (T* t) {
        destroy(t);
    }

    destroy_type destroy;
};
}

/*!
 *  Represent an Object loaded from a Shared Library (dll).
 *  The underlying object is accessed as if DynamicObject<> was
 *  a pointer.
 *
 *  You can choose the DO's behavior between shared_ptr or unique_ptr
 *  by default DO behave like a unique_ptr.
 *
 * Usage
 * -----
 *
 *  You have to have implemented a create and destroy function
 *  that allocate and deallocate the underlying object.
 *
 *  The create and destroy function default name are:
 *      - create_object
 *      - destroy_object
 *
 *  Those names can be overridden by calling
 *      create_functio_name() = "my_create_function_name";
 *      destroy_function_name() = "my_destroy_function_name";
 *
 *  You can also specify them during the DynamicObject creation
 *
 *      DynamicUnique<BaseObject> dyn_object("./libSharedLib.so", "my_create", "my_destroy");
 *
 *                      OR
 *
 *      DynamicShared<BaseObject> dyn_object("./libSharedLib.so", "my_create", "my_destroy");
 *
 * Usage
 * ----------
 *
 *  -*- Example 1 -*-
 *
 *    DynamicUnique<BaseObject> dyn_object("./libSharedLib.so");
 *
 *    dyn_object->what_ever_function();
 *
 * -*- Example 2 -*-
 *
 *    SharedLibrary sl("./libSharedLib.so");
 *
 *    DynamicUnique<BaseObject1> dyn_object1(sl);
 *
 *    DynamicShared<BaseObject2> dyn_object2(sl, "create2", "destroy2");
 *
 *
 * Warning
 * ----------
 *
 *  This Object does not prevent you from loading a 'Object1' as an 'Object2'
 *  doing so will make your program crash!
 *
 * Thought
 * -------
 *
 *  DynamicObject does not require a SharedLibrary for long.
 *  Could I remove it ? But then we don't know when the user will unload
 *  the SharedLibrary.
 *
 */

template<typename T, typename PtrType>
class DynamicObject
{
public:
    typedef typename internal::fun<T>::create create_type;
    typedef typename internal::fun<T>::destroy destroy_type;
    typedef T       value_type;
    typedef PtrType ptr_type;

    // Load a dynamic library
    DynamicObject(const std::string& path,
                  const std::string& create_name = create_function_name(),
                  const std::string& destroy_name = destroy_function_name()):
        _dynlib_ref(path)
    {
        // Make Sure both function are defined
        get_functions(create_name, destroy_name);
        create_object();
    }

    // Create a DynamicObject based on an existing SharedLibrary
    DynamicObject(const SharedLibrary& sl,
                  const std::string& create_name = create_function_name(),
                  const std::string& destroy_name = destroy_function_name()):
        _dynlib_ref(sl)
    {
        // Make Sure both function are defined
        get_functions(create_name, destroy_name);
        create_object();
    }

    DynamicObject(const DynamicObject& obj):
        _dynlib_ref(obj._dynlib_ref),
        _internal_dyn_object(obj._internal_dyn_object),
        _create(obj._create), _destroy(obj._destroy)
    {}

    // move constructor
    DynamicObject(DynamicObject&& obj) noexcept:
        _dynlib_ref(obj._dynlib_ref),
        _internal_dyn_object(std::move(obj._internal_dyn_object)),
        _create(obj._create), _destroy(obj._destroy)
    {}

    DynamicObject& operator=(const DynamicObject& rhs){
        // _dynlib_ref, _create, _destroy should already be equal
        rhs._internal_dyn_object = _internal_dyn_object;
        return *this;
    }

    inline value_type& operator* ()  {   return *_internal_dyn_object;   }
    inline value_type* operator->()  {   return _internal_dyn_object.get();     }

    inline SharedLibrary& shared_library() {   return _dynlib_ref;             }
    inline operator bool() const           {   return _internal_dyn_object;    }

    // Build a new object
    DynamicObject new_object(){
        DynamicObject d;
          d._dynlib_ref = _dynlib_ref;
          d._create     = _create;
          d._destroy    = _destroy;

        d.create_object();

        return d;
    }

private:

    // used when new_object() is called
    DynamicObject() {}

    void get_functions(const std::string& cname, const std::string& dname)
    {
        _create = _dynlib_ref.get_function_nocheck<create_type>(cname);
        THROW(_create == 0, std::runtime_error, "create method is undefined");

        _destroy = _dynlib_ref.get_function_nocheck<destroy_type>(dname);
        THROW(_destroy == 0, std::runtime_error, "destroy method is undefined");
    }

    void create_object(){
        // NB: the usage of a Deleter functor is not necessary for std::shared_ptr
        //     but is necessary for std::unique_ptr as pointer functions are not allowed
        _internal_dyn_object = ptr_type(_create(), internal::Deleter<value_type>(_destroy));
        THROW(!_internal_dyn_object, std::runtime_error, "create method call failure");
    }

private:
    SharedLibrary  _dynlib_ref;
    create_type    _create{nullptr};
    destroy_type   _destroy{nullptr};
    ptr_type       _internal_dyn_object{nullptr};
};

// we don't want our unique_ptr to clash with std::unique_ptr
namespace util{
template<typename T>
using unique_ptr = std::unique_ptr<T, internal::Deleter<T>>;
}

template<typename T>
using DynamicUnique = DynamicObject<T, util::unique_ptr<T>>;

template<typename T>
using DynamicShared = DynamicObject<T, std::shared_ptr<T>>;

}

#endif
