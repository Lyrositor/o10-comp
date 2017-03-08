find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

# In fact, CMake 3.3 and bellow forces you to use the following names for generated files
if (CMAKE_MAJOR_VERSION LESS 3 OR CMAKE_MINOR_VERSION LESS 4)
  # If CMAKE_VERSION < 3.4 (compat)
  BISON_TARGET(PARSER ${CMAKE_CURRENT_SOURCE_DIR}/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp
    COMPILE_FLAGS --defines="${CMAKE_CURRENT_BINARY_DIR}/parser.tab.hpp")
else ()
  # If CMAKE_VERSION >= 3.4 (stable)
  BISON_TARGET(PARSER ${CMAKE_CURRENT_SOURCE_DIR}/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp
    DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/parser.tab.hpp")
endif ()

if (CMAKE_MAJOR_VERSION LESS 3 OR CMAKE_MINOR_VERSION LESS 5)
  # If CMAKE_VERSION < 3.5 (compat)
  set(lexer_yy_h_path ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.h)
  FLEX_TARGET(SCANNER ${CMAKE_CURRENT_SOURCE_DIR}/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cpp
    COMPILE_FLAGS --header-file=${lexer_yy_h_path})
else ()
  # If CMAKE_VERSION >= 3.5 (stable)
  FLEX_TARGET(SCANNER ${CMAKE_CURRENT_SOURCE_DIR}/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cpp
    DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.h")
endif ()

ADD_FLEX_BISON_DEPENDENCY(SCANNER PARSER)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(parser STATIC ${BISON_PARSER_OUTPUTS} ${FLEX_SCANNER_OUTPUTS} parser.cpp)
target_link_libraries(parser ast)
