PROJECT(comp)

cmake_minimum_required(VERSION 2.8.12)
find_package(BISON 2.3)
find_package(FLEX 2.5.35)

set(CMAKE_CXX_STANDARD 11)

if (CMAKE_COMPILER_IS_GNUCXX )
  add_compile_options(-Wall -Wextra -pedantic -g)
endif ()

set(CMAKE_SOURCE_DIR src)

BISON_TARGET(MyParser src/lib/parser.yy ${PROJECT_SOURCE_DIR}/src/lib/parser.tab.cpp)
FLEX_TARGET(MyScanner src/lib/lexer.l ${PROJECT_SOURCE_DIR}/src/lib/lexer.cpp)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

include_directories("include/")

set(
        LIB_SOURCES
        include/comp/ast.h
        src/lib/ast.cpp
        src/lib/parser.tab.cpp
        src/lib/lexer.cpp
        src/lib/expr.cpp
)
add_library(comp SHARED ${LIB_SOURCES})
target_link_libraries(comp)

set(
  MAIN_SOURCES
  src/main/main.cpp
)
add_executable(comp_main ${MAIN_SOURCES})
target_link_libraries(comp_main comp)

add_subdirectory(vendor/googletest)
include_directories("${gtest_SOURCE_DIR}/include/" "${gtest_SOURCE_DIR}/")

set(
  TEST_SOURCES
  src/test/ast.spec.cpp
)
add_executable(comp_test ${TEST_SOURCES})
target_link_libraries(comp_test comp gtest gtest_main)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if (CMAKE_COMPILER_IS_GNUCXX)
  include(CodeCoverage)
  if (LCOV_PATH AND GENHTML_PATH)
    set(LCOV_REMOVE_EXTRA "'vendor/*'")
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage comp_test coverage)
  endif ()
endif ()
