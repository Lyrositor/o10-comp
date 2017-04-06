add_library(
  utils STATIC
  exceptions.cpp
)
target_link_libraries(utils ast)
