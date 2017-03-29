#pragma once

#include <cstddef>
#include <memory>
#include <string>

#include <comp/exceptions.h>

void PrintException(const comp::Exception &exception);

void PrintSyntaxException(
  const comp::SyntaxException &exception,
  const std::string &content,
  const char *filename);

size_t GetLineStartFromIndex(size_t start_idx, const std::string &content);

size_t GetLineEndFromIndex(size_t start_idx, const std::string &content);
