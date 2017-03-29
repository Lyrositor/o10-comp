#include "error_handling.h"

#include <iostream>
#include <vector>

#include <comp/ast/position.h>

static const unsigned int TAB_WIDTH = 8;

void PrintCompileException(
  const comp::CompileException &exception,
  const std::string &content,
  const char *filename) {
  std::shared_ptr<comp::ast::SourceLocation> l = exception.GetLocation();

  // Display the error and its message
  std::cerr << filename << ':';
  std::cerr << l->start.line + 1 << ':' << l->start.column + 1 << ':';
  std::cerr << " error: " << exception.what() << std::endl;

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
}
