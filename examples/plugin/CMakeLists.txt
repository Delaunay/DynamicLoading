
add_library(ex1_plugin1 SHARED ex1_plugin1.cpp)
add_library(ex1_plugin2 SHARED ex1_plugin2.cpp)

add_library(ex2_plugin1 SHARED ex2_plugin1.cpp)
add_library(ex2_plugin2 SHARED ex2_plugin2.cpp)

add_library(ex3_plugin1 SHARED ex3_plugin1.cpp)


SET(OBJ_SRC
    ../ObjType.h
    ../ObjType.cpp
)

add_library(ex4_plugin1 SHARED ex4_plugin1.cpp ${OBJ_SRC})


SET(OBJ2_SRC
    ../ObjType2.h
    ../ObjType2.cpp
)

add_library(ex5_plugin1 SHARED ex5_plugin1.cpp ${OBJ2_SRC})
