cmake_minimum_required(VERSION 2.8)
project(comp)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g -O0 -fprofile-arcs -ftest-coverage")

set(CMAKE_SOURCE_DIR src)

# include_directories("libs/simple_match/include/")

include_directories("include/")
set(
  LIB_SOURCES
  include/comp/ast.h
  src/lib/ast.cpp
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

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

message(${CMAKE_MODULE_PATH})

if (CMAKE_COMPILER_IS_GNUCXX)
  include(CodeCoverage)
  if (LCOV_PATH AND GENHTML_PATH)
    set(LCOV_REMOVE_EXTRA "'vendor/*'")
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage comp_test coverage)
  endif ()
endif ()
