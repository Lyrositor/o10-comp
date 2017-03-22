#include <comp/ast/to_json.h>
#include <comp/parser.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <string>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Incorrect arguments." << std::endl;
  } else {
    std::ifstream ifs(argv[1]);
    if (ifs.fail()) {
      std::cerr << strerror(errno) << std::endl;
      return 1;
    }
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    std::shared_ptr<comp::ast::Program> program = comp::parser::parse(content);

    std::unique_ptr<rapidjson::Document> document = comp::ast::ProgramToJson(*program);
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    document->Accept(writer);
    std::cout << buffer.GetString() << "\n";
  }
  return 0;
}
