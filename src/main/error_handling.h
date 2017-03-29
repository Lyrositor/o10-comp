#pragma once

#include <memory>
#include <string>

#include <comp/exceptions.h>

void PrintCompileException(
  const comp::CompileException &exception,
  const std::string &content,
  const char *filename);
