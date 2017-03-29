add_library(
  backend STATIC
  x64/build_asm.cpp
)
target_link_libraries(backend as)
