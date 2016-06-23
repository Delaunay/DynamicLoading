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
 *      DynamicObject<BaseObject> dyn_object("./libSharedLib.so", "my_create", "my_destroy");
 *
 * Usage
 * ----------
 *
 *  -*- Example 1 -*-
 *
 *    DynamicObject<BaseObject> dyn_object("./libSharedLib.so");
 *
 *    dyn_object->what_ever_function();
 *
 * -*- Example 2 -*-
 *
 *    SharedLibrary sl("./libSharedLib.so");
 *
 *    DynamicObject<BaseObject1> dyn_object1(sl);
 *
 *    DynamicObject<BaseObject2> dyn_object2(sl, "create2", "destroy2");
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

/*
template<typename T>
class Deleter
{
public:
    typedef void (*type)(T*);
};*/

template<typename T>
class Deleter{
public:
    typedef void (*destroy)(T*);

    Deleter() = default;

    Deleter(destroy t):
        _d(t)
    {}

    void operator() (T* t){
        _d(t);
    }

    destroy _d;
};

template<typename T, typename PtrType>
class DynamicObject
{
public:
    typedef T* (*create)();
    typedef void (*destroy)(T*);
    //typedef typename PtrType<T, destroy> PtrObject;

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

    inline T& operator* ()  {   return *_internal_dyn_object;   }
    inline T* operator->()  {   return _internal_dyn_object.get();     }

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

    void get_functions(const std::string& cname, const std::string& dname)
    {
        _create = _dynlib_ref.get_function_nocheck<create>(cname);
        THROW(_create == 0, std::runtime_error, "create method is undefined");

        _destroy = _dynlib_ref.get_function_nocheck<destroy>(dname);
        THROW(_destroy == 0, std::runtime_error, "destroy method is undefined");
    }

    void create_object();

    DynamicObject() {}

private:
    SharedLibrary _dynlib_ref;
    create    _create{nullptr};
    destroy   _destroy{nullptr};
    PtrType _internal_dyn_object{nullptr};
};

template<typename T, typename PtrType>
void DynamicObject<T, PtrType>::create_object()
{
    _internal_dyn_object = PtrType(_create());
    _internal_dyn_object.get_deleter() = Deleter<T>(_destroy);

    THROW(!_internal_dyn_object, std::runtime_error, "create method call failure");
}

// Need to make a partial specialization
//template<typename T>
//void DynamicObject<T, std::shared_ptr<T> >::create_object()
//{
//    _internal_dyn_object = std::shared_ptr<T>(_create(), _destroy);
//    //_internal_dyn_object.get_deleter() = Deleter<T>(_destroy);

//    THROW(!_internal_dyn_object, std::runtime_error, "create method call failure");
//}

template<typename T>
using DynamicUnique = DynamicObject<T, std::unique_ptr<T, Deleter<T> > >;

//template<typename T>
//using DynamicShared = DynamicObject<T, std::shared_ptr<T> >;

}

#endif
