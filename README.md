DynamicLoading
==============

[![Build Status](https://travis-ci.org/Delaunay/DynamicLoading.svg?branch=master)](https://travis-ci.org/Delaunay/DynamicLoading)

Load at runtime user defined objects. This library can be used to implement
hot reloading or plug-in systems. DynamicLoading works on Windows and Linux.

# Implementation

Shared libraries are warped around a `SharedLibrary` object which behave
like a `shared_ptr`.

User Object are warped around a `DynamicObject<T>` which can behave like a `unique_ptr` or a `shared_ptr`.

No safe guard are provided, i.e nothing prevent the programmer from
loading an object `T1` as an object `T2` which will result in an undefined behavior
(most likely a segmentation fault).


# Example 1

    // behave like a unique_ptr
    DynamicUnique<BaseObject> dyn_object("./libSharedLib.so");
      dyn_object->my_function();

    // behave like a shared_ptr
    DynamicShared<BaseObject> dyn_object("./libSharedLib.so");
      dyn_object->my_function():