add_library(
  ir STATIC
  optimizer/op_graph.cpp
  basic_block.cpp
  build_ir.cpp
  builtins.cpp
  context.cpp
  control_flow_graph.cpp
  data_type.cpp
  op.cpp
  program.cpp
  program_symbol.cpp
  symbol_table.cpp
  to_dot.cpp
  value.cpp
  variable.cpp
)
target_link_libraries(ir utils dot)