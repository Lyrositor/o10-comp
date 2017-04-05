#pragma once

#include <cstddef>
#include <memory>
#include <string>

#include <comp/utils/exceptions.h>

void PrintException(const std::exception &exception);

void PrintSyntaxException(
  const comp::CompilationException &exception,
  const std::string &content,
  const std::string &filename);

size_t GetLineStartFromIndex(size_t start_idx, const std::string &content);

size_t GetLineEndFromIndex(size_t start_idx, const std::string &content);
