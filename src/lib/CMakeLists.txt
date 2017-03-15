add_subdirectory(ast)
add_subdirectory(ir)
add_subdirectory(parser)

add_library(comp STATIC eval.cpp lib.cpp)
target_link_libraries(comp ast ir parser)
