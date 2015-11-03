SET(WINDOWS WIN32 || MSVC)

IF(WINDOWS)
    SET(SYSTEM_LIB )
ELSE()
    SET(SYSTEM_LIB -ldl)
ENDIF()


# plugin dir
add_subdirectory(plugin)

SET(HEADERS_BASE
    ex1_Base.h
    ex3_Base.h
    ex4_Base.h
    ex5_Base.h
)

SET(OBJ_SRC
    ObjType.h
    ObjType.cpp
)


add_executable(example1 example1.cpp ${HEADERS_BASE})
target_link_libraries(example1 plugin_library ${SYSTEM_LIB}) # -ldl is for linux only

add_executable(example2 example2.cpp)
target_link_libraries(example2 plugin_library ${SYSTEM_LIB}) # -ldl is for linux only

add_executable(example3 example3.cpp)
target_link_libraries(example3 plugin_library ${SYSTEM_LIB}) # -ldl is for linux only

add_executable(example4 example4.cpp ${OBJ_SRC} ex4_Base.h)
target_link_libraries(example4 plugin_library ${SYSTEM_LIB}) # -ldl is for linux only

# include eigen
INCLUDE_DIRECTORIES(C:/Users/pastafarian/Dropbox/libraries/include)

SET(OBJ2_SRC
    ObjType2.h
    ObjType2.cpp
)

add_executable(example5 example5.cpp ${OBJ_SRC} ex5_Base.h)
target_link_libraries(example5 plugin_library ${SYSTEM_LIB}) # -ldl is for linux only
