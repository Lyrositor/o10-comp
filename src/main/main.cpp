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

static const unsigned int TAB_WIDTH = 8;

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
  } catch (comp::CompileException & e) {
    std::shared_ptr<comp::ast::SourceLocation> l = e.GetLocation();

    // Display the error message
    std::cerr << argv[1] << ':';
    std::cerr << l->start.line + 1 << ':' << l->start.column + 1 << ':';
    std::cerr << " error: " << e.what() << std::endl;

    // Get the line which led to the error
    unsigned int line = 0;
    size_t idx = 0;
    size_t start_idx = 0;
    do {
      for (start_idx = idx; content[idx++] != '\n';) {
      }
    } while (line++ < l->start.line);
    size_t end_idx = idx - 1;

    // Display the line
    std::vector<char> underline;
    unsigned int pos = 1;
    for (idx = start_idx; idx < end_idx; idx++) {
      unsigned int width = 1;
      char c = content[idx];
      if (c == '\t') {
        width = -pos % TAB_WIDTH + 1;
        c = ' ';
      }

      for (unsigned int i = 0; i < width; i++) {
        std::cerr << c;
        if (idx - start_idx < l->start.column) {
          underline.push_back(' ');
        } else if (idx - start_idx < l->end.column) {
          underline.push_back('^');
        }
      }
      pos += width;
    }
    std::cerr << std::endl;

    // Display the underline
    for (char & c : underline) {
      std::cerr << c;
    }
    std::cerr << std::endl;

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
