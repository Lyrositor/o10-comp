add_subdirectory(ast)
add_subdirectory(parser)

add_library(comp SHARED eval.cpp lib.cpp)
target_link_libraries(comp ast parser)
