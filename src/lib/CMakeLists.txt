add_subdirectory(ast)
add_subdirectory(flex)

add_library(comp SHARED eval.cpp lib.cpp)
target_link_libraries(comp ast flex)
