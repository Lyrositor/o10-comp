#include <stdint.h>

int64_t x = -1;

int64_t foo(int32_t a, int32_t b) {
    return a + b;
}

void bar(int64_t new_x) {
    x = new_x;
}

int64_t main() {
    bar(5);
    return foo(10, 20);
}
