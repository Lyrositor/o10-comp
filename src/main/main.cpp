#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>

#include <comp/ast/to_json.h>
#include <comp/exceptions.h>
#include <comp/parser.h>

#include "error_handling.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Incorrect arguments." << std::endl;
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
      program = comp::parser::parse(content);

    std::unique_ptr<rapidjson::Document>
      document = comp::ast::ProgramToJson(*program);
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    document->Accept(writer);
    std::cout << buffer.GetString() << std::endl;
  } catch (comp::CompileException &e) {
    PrintCompileException(e, content, argv[1]);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
