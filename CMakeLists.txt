PROJECT(comp)

cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_CXX_STANDARD 11)

if (CMAKE_COMPILER_IS_GNUCXX)
  # add_compile_options(-Wall -Wextra -pedantic -g)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -g -O0 -fprofile-arcs -ftest-coverage")
endif ()

set(CMAKE_SOURCE_DIR src)


include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  include
  vendor/rapidjson/include
  vendor/optionparser/)
add_subdirectory(src/lib)

set(
  MAIN_SOURCES
  src/main/error_handling.cpp
  src/main/main.cpp
)
add_executable(comp_main ${MAIN_SOURCES})
target_link_libraries(comp_main comp)

add_subdirectory(vendor/googletest)
include_directories("${gmock_SOURCE_DIR}/include/" "${gtest_SOURCE_DIR}/include/")

set(
  TEST_SOURCES
  src/test/as/emit.spec.cpp
  src/test/ir/build_ir.spec.cpp
  src/test/ir/builtins.spec.cpp
  src/test/ir/context.spec.cpp
  src/test/ir/data_type.spec.cpp
  src/test/ir/variable.spec.cpp
  src/test/ast/ast.spec.cpp
  src/test/ast/to_json.spec.cpp
  src/test/parser/parser.spec.cpp
)
add_executable(comp_test ${TEST_SOURCES})
target_link_libraries(comp_test comp gtest gtest_main)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if (CMAKE_COMPILER_IS_GNUCXX)
  include(CodeCoverage)
  if (LCOV_PATH AND GENHTML_PATH)
    set(LCOV_REMOVE_EXTRA " 'vendor/*' ")
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage comp_test coverage)
  endif ()
endif ()
