PROJECT(comp)

cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_CXX_STANDARD 11)

if (CMAKE_COMPILER_IS_GNUCXX)
  # add_compile_options(-Wall -Wextra -pedantic -g)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -g -O0 -fprofile-arcs -ftest-coverage")
endif ()

set(CMAKE_SOURCE_DIR src)


include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(include)
add_subdirectory(src/lib)

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
  src/test/parser.spec.cpp
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
