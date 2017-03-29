#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <comp/ir/program.h>
#include <comp/ir/build_ir.h>
#include <comp/as/ast.h>
#include <comp/backend/x86/build_asm.h>
#include <comp/as/emit.h>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>

#include <comp/ast/to_json.h>
#include <comp/exceptions.h>
#include <comp/parser.h>

#include "error_handling.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Expected at least one argument" << std::endl;
    return EXIT_FAILURE;
  }

  std::ifstream ifs(argv[1]);
  if (ifs.fail()) {
    std::cerr << strerror(errno) << std::endl;
    return EXIT_FAILURE;
  }
  std::string content(
    (std::istreambuf_iterator<char>(ifs)),
    (std::istreambuf_iterator<char>()));

  try {
    std::shared_ptr<comp::ast::Program>
      programAst = comp::parser::parse(content);

    if (argc == 2) {
      std::unique_ptr<rapidjson::Document>
        document = comp::ast::ProgramToJson(*programAst);
      rapidjson::StringBuffer buffer;
      rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
      document->Accept(writer);
      std::cout << buffer.GetString() << std::endl;
    } else { // Example: comp_main main.c asm
      std::shared_ptr<comp::ir::Program> programIr = comp::ir::BuildProgramIR(*programAst);
      std::shared_ptr<comp::as::ast::Program> programAsm = comp::backend::x86::BuildProgram(*programIr);
      comp::as::emitProgram(*programAsm, std::cout);
    }
  } catch (comp::SyntaxException &e) {
    PrintSyntaxException(e, content, argv[1]);
    return EXIT_FAILURE;
  } catch  (comp::Exception &e) {
    PrintException(e);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
