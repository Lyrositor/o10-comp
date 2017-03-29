#include "error_handling.h"

#include <iostream>
#include <vector>

#include <comp/ast/position.h>

static const unsigned int TAB_WIDTH = 8;

void PrintException(const comp::Exception &exception) {
  std::cerr << "error: " << exception.what() << std::endl;
}

void PrintSyntaxException(
  const comp::SyntaxException &exception,
  const std::string &content,
  const char *filename) {
  std::shared_ptr<comp::ast::SourceLocation> l = exception.GetLocation();

  // Display the error and its message
  std::cerr << filename << ':';
  std::cerr << l->start.line + 1 << ':' << l->start.column + 1 << ':';
  std::cerr << " error: " << exception.what() << std::endl;

  // Get the line which led to the error
  size_t start_idx = GetLineStartFromIndex(l->start.index, content);
  size_t end_idx = GetLineEndFromIndex(l->end.index, content);

  // Display the line
  std::vector<char> underline;
  size_t idx;
  unsigned int display_col = 1;  // The current column, as displayed on-screen
  for (idx = start_idx; idx < end_idx; idx++) {
    unsigned int width = 1;
    char c = content[idx];
    if (c == '\t') {
      width = -display_col % TAB_WIDTH + 1;
      c = ' ';
    }

    for (unsigned int i = 0; i < width; i++) {
      std::cerr << c;
      if (idx < l->start.index) {
        underline.push_back(' ');
      } else if (idx < l->end.index) {
        underline.push_back('^');
      }
    }
    display_col += width;
  }
  std::cerr << std::endl;

  // Display the underline
  for (char & c : underline) {
    std::cerr << c;
  }
  std::cerr << std::endl;
}

size_t GetLineStartFromIndex(size_t start_idx, const std::string &content) {
  size_t idx = start_idx;
  while (idx-- > 0 && content[idx] != '\n') {
  }
  return idx + 1;  // Shift back to the line's first character
}

size_t GetLineEndFromIndex(size_t start_idx, const std::string &content) {
  size_t idx = start_idx;
  while (content[idx++] != '\n' && idx < content.size()) {
  }
  return idx - 1;  // Remove the newline
}
