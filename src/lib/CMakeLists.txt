add_subdirectory(as)
add_subdirectory(ast)
add_subdirectory(ir)
add_subdirectory(parser)

add_library(comp STATIC exceptions.cpp eval.cpp lib.cpp)
target_link_libraries(comp as ast ir parser)
