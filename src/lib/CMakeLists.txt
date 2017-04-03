add_subdirectory(as)
add_subdirectory(ast)
add_subdirectory(dot)
add_subdirectory(ir)
add_subdirectory(parser)
add_subdirectory(utils)

add_library(comp STATIC eval.cpp lib.cpp)
target_link_libraries(comp as ast dot ir parser utils)
