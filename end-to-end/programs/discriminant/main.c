#include <stdint.h>

int64_t main() {
  int64_t f;
  int64_t a = f;
  int64_t b = -f;
  int64_t c = f;
  int64_t d = b * b - f * a * c;
  return d;
}
