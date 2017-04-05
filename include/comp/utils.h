#pragma once

#include "comp/utils/exceptions.h"

#define UNUSED(expr) do { (void)(expr); } while (0)

struct EnumClassHash {
  template <typename T> std::size_t operator()(T t) const {
    return static_cast<std::size_t>(t);
  }
};
